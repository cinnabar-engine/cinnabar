FROM archlinux
RUN pacman -Syu --noconfirm && pacman -S base-devel cmake sdl2 glew glm doxygen --noconfirm --needed
# RUN mkdir /app
# RUN chown nobody:nobody /app -R
# RUN chmod 7777 /app -R
# USER nobody
WORKDIR /app
#RUN cd app
#RUN /packaging/create-arch.sh docker
#CMD bash -c "/app/create-arch.sh $@" docker  >> /proc/1/fd/1
