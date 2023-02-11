# Use the official Windows Server Core image
FROM mcr.microsoft.com/windows

# Set the working directory
WORKDIR /app

# Copy the library management system source code to the container
COPY . .

# Install the necessary dependencies
RUN powershell -Command \
    Add-WindowsFeature Net-Framework-Core, NET-Framework-45-ASPNET, \
    Web-Asp-Net45, Web-Net-Ext45, Web-ISAPI-Ext, Web-ISAPI-Filter, \
    Web-Includes, Web-WebSockets, Web-Default-Doc, Web-Dir-Browsing, \
    Web-Static-Content, Web-Performance, Web-Stat-Compression, \
    Web-Dyn-Compression, Web-Security, Web-Filtering, Web-Windows-Auth, \
    Web-App-Dev, Web-Net-Ext, Web-Net-Ext45, Web-ASP, Web-CGI, \
    Web-Client-Auth, Web-Digest-Auth, Web-Dir-Browsing, Web-Dyn-Compression, \
    Web-Http-Errors, Web-Http-Logging, Web-Http-Redirect, Web-Http-Tracing, \
    Web-ISAPI-Ext, Web-ISAPI-Filter, Web-Lgcy-Mgmt-Console, Web-Metabase, \
    Web-Mgmt-Console, Web-Mgmt-Service, Web-Net-Ext, Web-Request-Monitor, \
    Web-Server, Web-Stat-Compression, Web-Static-Content, Web-Windows-Auth, \
    Web-WMI, MSIPC-Client; \
    Invoke-WebRequest -Uri "https://sourceforge.net/projects/mingw/files/MinGW/BaseSystem/mingw-get-0.6.3/mingw-get-0.6.3-mingw32-bin.tar.lzma/download" -OutFile "mingw-get.tar.lzma"; \
    tar -xf mingw-get.tar.lzma; \
    mingw-get-0.6.3-mingw32-bin/mingw-get.exe install -y mingw32-base, mingw32-gcc-g++, mingw32-ncurses

# Build the library management system
RUN mingw32-make

# Set the default command to run the library management system
CMD ["./library_rentals_management_system.exe"]
