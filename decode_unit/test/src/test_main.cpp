
#include "matrix_extract_tests.hpp"

pthread_mutex_t g_MutLapack;

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
