FROM archlinux
RUN pacman -Syu --noconfirm && pacman -S base-devel sdl2 glew glm assimp --noconfirm --needed
COPY . /app
RUN chown nobody:nobody /app -R && chmod 777 /app -R
USER nobody
RUN cd app
#RUN /packaging/create-arch.sh docker
#CMD bash -c "/app/create-arch.sh $@" docker  >> /proc/1/fd/1