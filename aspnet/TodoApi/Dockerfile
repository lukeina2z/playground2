# Use the official .NET image from Microsoft as the base image
FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
WORKDIR /app
ENV ASPNETCORE_URLS=http://0.0.0.0:80
EXPOSE 80

# Use the SDK image to build the app
FROM mcr.microsoft.com/dotnet/sdk:8.0 AS build
WORKDIR /src
COPY TodoApi.csproj TodoApi/
RUN dotnet restore "TodoApi/TodoApi.csproj"
COPY . ./TodoApi
WORKDIR "/src/TodoApi"
RUN dotnet build "TodoApi.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "TodoApi.csproj" -c Release -o /app/publish

# Copy the app files to the final image and set entry point
FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "TodoApi.dll"]
