FROM chriamue/annotatorlib:cpu
MAINTAINER chriamue@gmail.com

# based on https://github.com/anurag/fastai-course-1/blob/master/Dockerfile

ARG PYTHON_VERSION=2.7
ARG TINI_VERSION=v0.13.2
ARG USERNAME=annotator
ARG USERID=1000

RUN apt-get update && \
  apt-get install -y --no-install-recommends git wget ffmpeg unzip sudo

ADD https://github.com/krallin/tini/releases/download/$TINI_VERSION/tini /tini
RUN chmod +x /tini

RUN useradd --create-home -s /bin/bash --no-user-group -u $USERID $USERNAME && \
  adduser $USERNAME sudo && \
  echo "$USERNAME ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

USER $USERNAME
WORKDIR /home/$USERNAME

RUN pip install --upgrade pip && pip install notebook ipywidgets matplotlib

# Jupyter
EXPOSE 8888

ENTRYPOINT ["/tini", "--"]
CMD jupyter notebook --ip=0.0.0.0 --port=8888