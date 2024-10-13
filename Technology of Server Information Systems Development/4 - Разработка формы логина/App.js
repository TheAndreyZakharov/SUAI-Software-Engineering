    angular.module('stockManager', [])
        .controller('StockController', ['$http', '$window', function($http, $window) {
            var self = this;
            self.stocks = [];
            self.newStock = {};
            self.stockToSell = {};

            self.loadStocks = function() {
                if (!$window.localStorage.getItem('token')) {
                    alert('Пожалуйста, войдите в систему для доступа к акциям.');
                    return;
                }
                $http.defaults.headers.common['Authorization'] = 'Bearer ' + $window.localStorage.getItem('token');
                $http.get('/stocks').then(function(response) {
                    self.stocks = response.data;
                }, function(error) {
                    alert('Ошибка при загрузке акций ' + error.statusText);
                });
            };

            self.buyStock = function() {
                $http.defaults.headers.common['Authorization'] = 'Bearer ' + $window.localStorage.getItem('token');
                $http.post('/buyStock', null, { params: self.newStock }).then(function(response) {
                    alert('Акция успешно куплена!');
                    self.loadStocks();
                }, function(error) {
                    alert('Ошибка при покупке акции ' + error.statusText);
                });
            };

            self.sellStock = function() {
                $http.defaults.headers.common['Authorization'] = 'Bearer ' + $window.localStorage.getItem('token');
                $http.post('/sellStock', null, { params: self.stockToSell }).then(function(response) {
                    alert('Акция успешно продана!');
                    self.loadStocks();
                }, function(error) {
                    alert('Ошибка при продаже акции ' + error.statusText);
                });
            };

            self.loadStocks();
        }])


        .controller('LoginCtrl', ['$scope', '$http', '$window', function($scope, $http, $window) {
            $scope.login = function() {
                var data = "username=" + encodeURIComponent($scope.username) +
                    "&password=" + encodeURIComponent($scope.password);

                $http.post('/login', data, {
                    headers: {'Content-Type': 'application/x-www-form-urlencoded'}
                }).then(function(response) {
                    var token = response.data.token;  // Извлечение JWT из ответа
                    $window.localStorage.setItem('token', token);  // Сохранение JWT в локальном хранилище
                    $window.localStorage.setItem('username', $scope.username);  // Сохранение имени пользователя
                    $window.location.href = '/';  // Перенаправление на главную страницу
                }, function(error) {
                    alert('Ошибка входа: ' + error.statusText);
                });
            };
        }])

        // Периодическая проверка валидности токена
        .run(['$rootScope', '$window', '$interval', function($rootScope, $window, $interval) {
            $interval(function() {
                var token = $window.localStorage.getItem('token');
                if (token) {
                    var payload = JSON.parse($window.atob(token.split('.')[1]));

                    // Логирование для отладки
                    console.log('Текущее время (в секундах):', Date.now() / 1000);
                    console.log('Время истечения токена:', payload.exp);

                    if (payload.exp < Date.now() / 1000) {
                        $window.localStorage.removeItem('token');
                        $rootScope.$broadcast('UserLoggedOut');
                        alert('Ваша сессия истекла. Пожалуйста, войдите снова.');
                    }
                }
            }, 600000); // Проверка каждые 10 минут
        }]);


