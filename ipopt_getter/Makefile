all:
	docker build --build-arg UID=$(shell id -u) --build-arg GID=$(shell id -g) --build-arg USER=$(shell whoami) -t fetch_gitlab_artifacts .
	docker run -it --rm -v $(shell pwd):/out --net=host -e USER=$(shell whoami) -e UID=$(shell id -u) -e GID=$(shell id -g) --net=host fetch_gitlab_artifacts --project_id 56 --target_branch with-third-parties --build_stage=run
	unzip artifacts.zip
	rm artifacts.zip
	rm -rf install
