FROM ubuntu:latest
# MAINTAINER turbstructor ycw1905@gmail.com

RUN set -xe && apt-get -qq update && apt-get -y -qq upgrade
RUN set -xe && DEBIAN_FRONTEND=noninteractive apt-get -y -qq install apt-utils tzdata locales

ENV TZ=Asia/Seoul
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN set -xe && dpkg-reconfigure --frontend=noninteractive tzdata

RUN set -xe && \
    sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    sed -i -e 's/# ko_KR.UTF-8 UTF-8/ko_KR.UTF-8 UTF-8/' /etc/locale.gen && \
    echo 'LANG="en_US.UTF-8"' > /etc/default/locale && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=en_US.UTF-8

ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

RUN yes | unminimize
RUN set -xe && apt-get -qq update --fix-missing && apt-get -y -qq upgrade

# Install packages needed
RUN apt-get -y -qq install \
        vim wget man sudo git zsh \
        tmux bat \
        gcc-multilib libncurses5-dev libncursesw5-dev

RUN set -xe \
    && useradd -m -g users -G sudo -s $(which zsh) manager && passwd -d manager \
    && useradd -m -g users -G sudo -s $(which zsh) player && passwd -d player

USER manager
WORKDIR /home/manager/

# Link bat to batcat
RUN sudo ln -s /usr/bin/batcat /usr/local/bin/bat

# Install zsh and oh-my-zsh
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.1/zsh-in-docker.sh)" -- \
    -t https://github.com/yarisgutierrez/classyTouch_oh-my-zsh
RUN sudo chsh -s $(which zsh)
ADD --chown=manager:users base/classyTouch.zsh-theme ./.oh-my-zsh/custom/themes/classyTouch_oh-my-zsh/classyTouch.zsh-theme
ADD --chown=manager:users base/.zshrc .


# Install Pwndbg
RUN set -xe && git clone https://github.com/pwndbg/pwndbg .pwndbg && cd .pwndbg && ./setup.sh

# Install Splitmind-Tmux for Pwndbg
RUN set -xe && git clone https://github.com/jerdna-regeiz/splitmind .splitmind
ADD --chown=manager:users base/.tmux.conf .

# Install pwntools via pip
RUN sudo pip3 install pwntools

# ENV PATH="/usr/local/lib/python3.8/dist-packages/bin:$PATH"

# Install checksec
RUN set -xe && git clone https://github.com/slimm609/checksec.sh .checksec && sudo ln -sf ~/.checksec/checksec /usr/bin/checksec


# Initialize player and every sectors
RUN sudo cp .zshrc /home/player/ && sudo chown player:users /home/player/.zshrc
RUN sudo cp .tmux.conf /home/player/ && sudo chown player:users /home/player/.tmux.conf

ADD --chown=manager:users initialize.sh .
RUN sudo ./initialize.sh

# Initialize every sectors with shell scripts
USER sectorA
WORKDIR /home/sectorA

RUN mkdir programmerbase
COPY --chown=sectorA:users programmerbase programmerbase/
RUN cd programmerbase && sudo ./initialize.sh
RUN rm -rf programmerbase


USER sectorB
WORKDIR /home/sectorB

RUN mkdir machinelearning
COPY --chown=sectorB:users machinelearning machinelearning/
RUN cd machinelearning && sudo ./initialize.sh
RUN rm -rf machinelearning


USER sectorC
WORKDIR /home/sectorC

RUN mkdir algorithm
COPY --chown=sectorC:users algorithm algorithm/
RUN cd algorithm && sudo ./initialize.sh
RUN rm -rf algorithm


USER sectorD
WORKDIR /home/sectorD

RUN mkdir network
COPY --chown=sectorD:users network network/
RUN cd network && sudo ./initialize.sh
RUN rm -rf network


USER root
WORKDIR /home/manager

ADD --chown=manager:users security/.gdbinit .

RUN mkdir security
COPY --chown=manager:users security security/
RUN cd security && ./initialize.sh
RUN cd security && ./re-initialize.sh

# Configure security phase

# USER player
# WORKDIR /home/player/

# RUN mkdir security
# WORKDIR /home/manager/security/

# RUN mkdir prototypes
# COPY --chown=manager:users prototypes ./prototypes/
# ADD --chown=root:root initialize.sh ./.initialize.sh
# ADD --chown=manager:users decode.c .
# RUN gcc -o /home/sectorE/decode decode.c && sudo chown root:root /home/sectorE/decode && sudo chmod 6755 /home/sectorE/decode
# # RUN cp ./decode /home/sectorE/
# RUN cp ./.initialize.sh /home/sectorE/

# USER sectorE
# WORKDIR /home/sectorE/
# RUN sudo ./.initialize.sh
# RUN sudo chmod 0700 initialize.sh

# USER root
# RUN usermod -p $(openssl passwd -crypt $(echo "deadbeef")) manager

USER root
RUN set -xe \
    && usermod -G users sectorA \
    && usermod -G users sectorB \
    && usermod -G users sectorC \
    && usermod -G users sectorD \
    && usermod -G users sectorE \
    && usermod -G users player

RUN chmod 711 /home/manager
RUN usermod -p $(openssl passwd -crypt $(echo "deadbeef")) manager

RUN useradd -m -g users -s $(which zsh) -p $(openssl passwd -crypt $(echo "password")) outside
ADD --chown=root:root .zshrc_final /home/outside/.zshrc
ADD --chown=root:root readme.md_final /home/outside/Readme.md

WORKDIR "/home/player/"
ADD --chown=root:root decode_main.c .
RUN gcc -o decode_main decode_main.c && chown root:root decode_main && chmod 6755 decode_main
RUN rm decode_main.c
RUN echo "0 0 0 0 0" > ".lock_slots"

USER player
WORKDIR "/home/player"
CMD ["zsh"]