angular.module('stockManager', [])
    .controller('StockController', ['$http', function($http) {
        var self = this;
        self.stocks = [];
        self.newStock = {};
        self.stockToSell = {};

        self.loadStocks = function() {
            $http.get('/stocks').then(function(response) {
                self.stocks = response.data;
            }, function(error) {
                console.error('Error while fetching stocks', error);
            });
        };

        self.buyStock = function() {
            $http.post('/buyStock', null, { params: self.newStock }).then(function(response) {
                alert(response.data.message);
                self.loadStocks();
            }, function(error) {
                console.error('Error while buying stock', error);
            });
        };

        self.sellStock = function() {
            $http.post('/sellStock', null, { params: self.stockToSell }).then(function(response) {
                alert(response.data.message);
                self.loadStocks();
            }, function(error) {
                console.error('Error while selling stock', error);
            });
        };

        self.loadStocks(); // Load stocks on controller init
    }]);
