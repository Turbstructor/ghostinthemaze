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
RUN chmod 711 /home/manager

RUN set -xe && useradd -m -g users -G sudo -s $(which zsh) playerA && passwd -d playerA && \
    useradd -m -g users -G sudo -s $(which zsh) playerB && passwd -d playerB && \
    useradd -m -g users -G sudo -s $(which zsh) playerC && passwd -d playerC && \
    useradd -m -g users -G sudo -s $(which zsh) playerD && passwd -d playerD && \
    useradd -m -g users -G sudo -s $(which zsh) playerE && passwd -d playerE

USER manager
WORKDIR /home/manager/

# Link bat to batcat
RUN sudo ln -s /usr/bin/batcat /usr/local/bin/bat

# Install zsh and oh-my-zsh
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.1/zsh-in-docker.sh)" -- \
    -t https://github.com/yarisgutierrez/classyTouch_oh-my-zsh
RUN sudo chsh -s $(which zsh)
ADD --chown=manager:users classyTouch.zsh-theme ./.oh-my-zsh/custom/themes/classyTouch_oh-my-zsh/classyTouch.zsh-theme
ADD --chown=manager:users .zshrc .

# Install Pwndbg
RUN set -xe && git clone https://github.com/pwndbg/pwndbg .pwndbg && cd .pwndbg && ./setup.sh

# Install Splitmind-Tmux for Pwndbg
RUN set -xe && git clone https://github.com/jerdna-regeiz/splitmind .splitmind
ADD --chown=manager:users .gdbinit .
ADD --chown=manager:users .tmux.conf .

# Install pwntools via pip
RUN sudo pip3 install pwntools

ENV PATH="/usr/local/lib/python3.8/dist-packages/bin:$PATH"

# Install checksec
RUN set -xe && git clone https://github.com/slimm609/checksec.sh .checksec && sudo ln -sf ~/.checksec/checksec /usr/bin/checksec

# Configure security phase

# USER player
# WORKDIR /home/player/

# RUN mkdir security
# WORKDIR /home/manager/security/

# RUN mkdir prototypes
# COPY --chown=manager:users prototypes ./prototypes/
# ADD --chown=root:root initialize.sh ./.initialize.sh
# ADD --chown=manager:users decode.c .
# RUN gcc -o /home/playerE/decode decode.c && sudo chown root:root /home/playerE/decode && sudo chmod 6755 /home/playerE/decode
# # RUN cp ./decode /home/playerE/
# RUN cp ./.initialize.sh /home/playerE/

# USER playerE
# WORKDIR /home/playerE/
# RUN sudo ./.initialize.sh
# RUN sudo chmod 0700 initialize.sh

# USER root
# RUN usermod -p $(openssl passwd -crypt $(echo "deadbeef")) manager
# RUN usermod -G users player

USER player
CMD ["zsh"]