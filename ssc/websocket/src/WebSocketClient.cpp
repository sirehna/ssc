/*
 * WebSocketEndpoint.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: cady
 */

#include <unistd.h> //usleep

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include "ConnectionMetadata.hpp"
#include "ssc/websocket/WebSocketClient.hpp"
#include "ssc/websocket/WebSocketException.hpp"

using namespace ssc::websocket;

struct Client::Impl
{
    std::string append_port_to_address(const std::string& address, const short unsigned int port)
    {
        std::stringstream ss;
        ss << address << ":" << port;
        return ss.str();
    }

    void throw_if_time_out(const size_t counter) const
    {
        if (counter>100)
        {
            std::cerr << "In file " << __FILE__ << ", line " << __LINE__ << ": timeout when attempting connexion to websocket." << std::endl;
            std::stringstream ss;
            ss << "Time out when retrieving metadata from the endpoint" << std::endl;
            THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
        }
    }

    bool connected(const size_t k)
    {
        ConnectionMetadata::ptr metadata = get_metadata(next_id);
        throw_if_time_out(k);
        if (metadata->get_status()=="Open") return true;
        if (metadata->get_status()=="Failed")
        {
            std::cerr << "In file " << __FILE__ << ", line " << __LINE__ << ": Unable to open websocket." << std::endl;
            THROW(__PRETTY_FUNCTION__, WebSocketException, "Unable to open websocket");
        }
        usleep(100000);
        return false;
    }

    void prepare_endpoint()
    {
        endpoint.clear_access_channels(websocketpp::log::alevel::all);
        endpoint.clear_error_channels(websocketpp::log::elevel::all);
        endpoint.init_asio();
        endpoint.start_perpetual();
    }

    Impl() : endpoint(), websocket_thread(), id_to_connection(), next_id(0)
    {
    }

    Impl(std::string address, const short unsigned int port) : endpoint(), websocket_thread(), id_to_connection(), next_id(0)
    {
        address = append_port_to_address(address, port);
        prepare_endpoint();
        websocket_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &endpoint);
        usleep(10000);
        size_t k=0;
        connect(address);
        bool is_connected = false;
        while(not(is_connected = connected(k))) k++;
        if (not(is_connected))
        {
            std::cerr << "In file " << __FILE__ << ", line " << __LINE__ << ": timeout when attempting connexion to websocket at address" << address << std::endl;
        }
    }

    void set_handlers(const client::connection_ptr& con, const ConnectionMetadata::ptr& metadata_ptr)
    {
        con->set_open_handler(websocketpp::lib::bind(
            &ConnectionMetadata::on_open,
            metadata_ptr,
            &endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_fail_handler(websocketpp::lib::bind(
            &ConnectionMetadata::on_fail,
            metadata_ptr,
            &endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_close_handler(websocketpp::lib::bind(
            &ConnectionMetadata::on_close,
            metadata_ptr,
            &endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_message_handler(websocketpp::lib::bind(
            &ConnectionMetadata::on_message,
            metadata_ptr,
            websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2
        ));
    }

    /**
     * \param[in] uri
     * \note
     * The \param uri can looks like
     *  - "ws://localhost:9002"
     *  - "ws://localhost:9002/ws?username=me"
     */
    void connect(std::string const & uri)
    {
        websocketpp::lib::error_code error_code;
        client::connection_ptr con = endpoint.get_connection(uri, error_code);
        if (error_code)
        {
            std::stringstream ss;
            ss << "Unable to get a connection to " << uri << ": " << error_code.message() << std::endl;
            std::cerr << ss.str() << "Throwing an exception which might crash the program";
            THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
        }
        next_id++;
        ConnectionMetadata::ptr metadata_ptr = websocketpp::lib::make_shared<ConnectionMetadata>(next_id, con->get_handle(), uri);
        id_to_connection[next_id] = metadata_ptr;
        set_handlers(con, metadata_ptr);
        endpoint.connect(con);
    }

    void close(const ConnectionMetadata::ptr& connexion)
    {
        // Only close open connections
        if (connexion->get_status() != "Open") return;
        websocketpp::lib::error_code error_code;
        endpoint.close(connexion->get_hdl(), websocketpp::close::status::going_away, "", error_code);
        if (error_code)
        {
            std::stringstream ss;
            ss << "Error closing connection " << connexion->get_id() << ": "
               << error_code.message() << std::endl;
            THROW(__PRETTY_FUNCTION__, WebSocketException,ss.str());
        }
    }

    void send(const int id, const std::string& message)
    {
        websocketpp::lib::error_code error_code;
        IdToConnexionMap::iterator metadata_it = id_to_connection.find(id);
        if (metadata_it == id_to_connection.end())
        {
            std::stringstream ss;
            ss << "Could not send message to connection: id " << id << " not found: " << error_code.message();
            THROW(__PRETTY_FUNCTION__, WebSocketException,ss.str());
        }
        auto hdl = metadata_it->second->get_hdl();
        endpoint.send(hdl, message, websocketpp::frame::opcode::text, error_code);
        if (error_code)
        {
            std::stringstream ss;
            ss << "Error sending message: " << error_code.message() << std::endl;
            THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
            return;
        }
        metadata_it->second->record_sent_message(message);
    }

    ConnectionMetadata::ptr get_metadata(const int id) const
    {
        IdToConnexionMap::const_iterator metadata_it = id_to_connection.find(id);
        if (metadata_it == id_to_connection.end())
        {
            std::stringstream ss;
            ss << "Unknown connection id : " << next_id << std::endl;
            THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
        }
        return metadata_it->second;
    }

    typedef std::map<int,ConnectionMetadata::ptr> IdToConnexionMap;
    client endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> websocket_thread;
    IdToConnexionMap id_to_connection;
    int next_id;
};

Client::Client(const std::string& address, const short unsigned int port) : pimpl(new Impl(address, port))
{
}

Client::Client() : pimpl(new Impl())
{
}

Client::~Client()
{
    pimpl->endpoint.stop_perpetual();
    for (const auto id2connection:pimpl->id_to_connection) pimpl->close(id2connection.second);
    pimpl->websocket_thread->join();
}

bool Client::good() const
{
    return pimpl->next_id != -1;
}

void Client::send_text(const std::string& message)
{
    pimpl->send(pimpl->next_id, message);
}

void Client::send_vector(void const * payload, const size_t nb_of_bytes)
{
    send_vector(pimpl->next_id, payload, nb_of_bytes);
}

void Client::send_vector(const int id, void const * payload, const size_t nb_of_bytes)
{
    websocketpp::lib::error_code error_code;
    Impl::IdToConnexionMap::iterator metadata_it = pimpl->id_to_connection.find(id);
    if (metadata_it == pimpl->id_to_connection.end())
    {
        std::stringstream ss;
        ss << "Unknown connection id : " << id << std::endl;
        THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
    }
    auto handle = metadata_it->second->get_hdl();
    pimpl->endpoint.send(handle, payload, nb_of_bytes, websocketpp::frame::opcode::binary, error_code);
    if (error_code)
    {
        std::stringstream ss;
        ss << "Error sending message: " << error_code.message() << std::endl;
        THROW(__PRETTY_FUNCTION__, WebSocketException, ss.str());
        return;
    }
}
