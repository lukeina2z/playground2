


Tutorial: Create a web API with ASP.NET Core
https://learn.microsoft.com/en-us/aspnet/core/tutorials/first-web-api?view=aspnetcore-9.0&tabs=visual-studio-code


dotnet dev-certs https --trust


dotnet run --launch-profile https

http://localhost:5116/swagger/index.html

http://localhost:5116/weatherforecast

curl -X 'GET' \
  'http://localhost:5116/WeatherForecast' \
  -H 'accept: text/plain'

curl -X 'GET' \
  'http://localhost:5116/api/TodoItems' \
  -H 'accept: text/plain'

curl -X 'POST' \
  'http://localhost:5116/api/TodoItems' \
  -H 'accept: text/plain' \
  -H 'Content-Type: application/json' \
  -d '{
  "name": "grocery shopping",
  "isComplete": false
}'

curl -X 'GET' \
  'http://localhost:5116/api/TodoItems/2' \
  -H 'accept: text/plain'

curl -X 'PUT' \
  'http://localhost:5116/api/TodoItems/1' \
  -H 'accept: */*' \
  -H 'Content-Type: application/json' \
  -d '{
"id": 1,
"name":"grocery shopping",
  "isComplete": true
}'

curl -X 'DELETE' \
  'http://localhost:5116/api/TodoItems/1' \
  -H 'accept: */*'
