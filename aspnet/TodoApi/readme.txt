


Tutorial: Create a web API with ASP.NET Core
https://learn.microsoft.com/en-us/aspnet/core/tutorials/first-web-api?view=aspnetcore-9.0&tabs=visual-studio-code


dotnet dev-certs https --trust

dotnet run --launch-profile https



docker build --no-cache -t todo-img-01 .

docker run -d -p 8090:80 --name MyToDoApp todo-img-01




http://localhost:8080/swagger/index.html

http://localhost:8080/weatherforecast

curl -X 'GET' \
  'http://localhost:8080/WeatherForecast' \
  -H 'accept: text/plain'

curl -X 'GET' \
  'http://localhost:8080/api/TodoItems' \
  -H 'accept: text/plain'

curl -X 'POST' \
  'http://localhost:8080/api/TodoItems' \
  -H 'accept: text/plain' \
  -H 'Content-Type: application/json' \
  -d '{
  "name": "grocery shopping",
  "isComplete": false
}'

curl -X 'GET' \
  'http://localhost:8080/api/TodoItems/2' \
  -H 'accept: text/plain'

curl -X 'PUT' \
  'http://localhost:8080/api/TodoItems/1' \
  -H 'accept: */*' \
  -H 'Content-Type: application/json' \
  -d '{
"id": 1,
"name":"grocery shopping",
  "isComplete": true
}'

curl -X 'DELETE' \
  'http://localhost:8080/api/TodoItems/1' \
  -H 'accept: */*'
