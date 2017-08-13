FROM chriamue/annotatorlib:cpu
MAINTAINER chriamue@gmail.com

# based on https://github.com/anurag/fastai-course-1/blob/master/Dockerfile

ARG PYTHON_VERSION=2.7
ARG TINI_VERSION=v0.13.2
ARG USERNAME=annotator
ARG USERID=1000
ENV PYTHONIOENCODING UTF-8

RUN apt-get update && \
  apt-get install -y --no-install-recommends whois git wget unzip python-setuptools python-pip
RUN pip install --upgrade pip && pip install ipykernel notebook ipywidgets matplotlib
ADD https://github.com/krallin/tini/releases/download/$TINI_VERSION/tini /tini
RUN chmod +x /tini

RUN useradd --create-home -s /bin/bash --no-user-group -u $USERID $USERNAME

USER $USERNAME

WORKDIR /home/$USERNAME

RUN cp /annotatorlib/deploy/docker/ipynb/flickr.pro.xml /home/$USERNAME/ && \
    cp /annotatorlib/deploy/docker/ipynb/flickr.json /home/$USERNAME/ && \
    cp /annotatorlib/deploy/docker/ipynb/pyannotatorlib.ipynb /home/$USERNAME/

# Add a notebook profile.
# Password: annotator
RUN mkdir -p -m 700 .jupyter/ && \
    echo "c.NotebookApp.password = u'sha1:793382ba2d2f:56c056ed79f16d09f1dd1c99c29b91d1763176bb'\nc.NotebookApp.ip = '*'" >> .jupyter/jupyter_notebook_config.py

# Jupyter
EXPOSE 8888

ENTRYPOINT ["/tini", "--"]
CMD jupyter notebook --ip=0.0.0.0 --port=8888