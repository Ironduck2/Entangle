# 1. Usar una imagen base oficial de Nginx en su versión Alpine (súper ligera)
FROM nginx:alpine

# 2. Copiar todo el contenido de tu carpeta 'web' a la carpeta pública de Nginx
COPY ./web /usr/share/nginx/html

# 3. Exponer el puerto 80 (el puerto estándar de la web)
EXPOSE 80