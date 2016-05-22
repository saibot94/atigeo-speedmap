(function() {
	'use strict';

	var app = angular.module('SrcApp', ['nvd3','uiGmapgoogle-maps', 'ui.bootstrap', 'ngRoute',
	 'ngAnimate', 'ngMaterial', 'ngAria', 'rzModule']).config(
	    ['uiGmapGoogleMapApiProvider', function(GoogleMapApiProviders) {
	        GoogleMapApiProviders.configure({
	            china: true,
        		libraries: 'weather,geometry,visualization'

	        });
	    }]
	);


	app.config(['$routeProvider',
      function($routeProvider) {
        $routeProvider.
          when('/dashboard', {
            templateUrl: 'templates/dashboard.html',
            controller: 'MainController',
            controllerAs: 'mainController',
            resolve:  {
                loc: function($q, LocationService, ApiSearchService){
                    return ApiSearchService.GetCoordinates(LocationService.GetLocation());
                }
            }

          }).
          when('/analytics', {
            templateUrl: 'templates/analytics.html',
            controller: 'AnalyticsController'
          }).
          when('/', {
            templateUrl: 'templates/search.html',
            controller: 'SearchController',
            controllerAs: 'vm'
          }).
          otherwise({
            redirectTo: '/'
          });
    }]);


	app.controller('MainController', MainController);

	MainController.$inject = ['$scope', 'ApiAggregateService', '$sce','$filter', '$q','LocationService', 'loc'];

	function MainController($scope, ApiAggregateService, $sce, $filter, $q, LocationService, loc){

		var vm = this;


		console.log('locatino: ' + loc);
        vm.location = loc.data.results[0].formatted_address;//address_components[0].long_name;
        console.log(loc.data.results[0].geometry.bounds);
        LocationService.SetBounds(loc.data.results[0].geometry.bounds);


		vm.searchResults = [];
		vm.aggregatesByLanguageVeniceNoIt = [];
		vm.aggregatesByLanguage = [];
		vm.aggregatesByCountry = [];
		vm.aggregatesByCity = [];
		vm.aggregatesByUserHighestRatio = [];
		vm.aggregatesByUserMostTweets = [];
		vm.aggregatesByUserMostFollowers = [];

		vm.searchOption = 'direct';
		vm.searchString = null;
		vm.resonseTotal = 0;
		vm.scopeLimit = 25;
		vm.formModel = {};

		var init = function () {
			vm.searchResults = [];
			vm.aggregatesByLanguageVeniceNoIt = [];
			vm.aggregatesByLanguage = [];
			vm.aggregatesByCountry = [];
			vm.aggregatesByCity = [];
			vm.aggregatesByUserHighestRatio = [];
			vm.aggregatesByUserMostTweets = [];
			vm.aggregatesByUserMostFollowers = [];
			vm.aggregatesByHashtag = [];
		}

		init();
		// vm.search = function(){
		// 	if(vm.searchString ){
		// 		vm.searching = true;
		// 		vm.searchResults = null;
		// 		vm.resonseTotal = 0;
		// 		vm.scopeLimit = 25;
		// 		vm.searchOption = vm.searchOption || 'direct';
		// 		ApiSearchService.Search(vm.searchString, vm.searchOption).then(function (resonse) {
		// 			vm.resonseTotal = resonse.data.results.length;
		// 			vm.searchResults = resonse.data.results;
		// 			vm.searching = false;

		// 		})	
		// 	}
		// }
		vm.getAggregates = function(){
			init();
			getVeniceAreaTweetsNoIt();
			getByLanguage();
			getPlaceAggregates();
			getUserAggregates();
			getHashtagAggregates();
		}

		var getHashtagAggregates = function(){
			ApiAggregateService.GetHashtagOccurences(vm.formModel.dateFrom, vm.formModel.dateTo).then(function(res){
				vm.aggregatesByHashtag = res.data.results;
			});
		}

		var getVeniceAreaTweetsNoIt = function(){
			ApiAggregateService.GetByLanguageVeniceTweetsNoIt(vm.formModel.dateFrom, vm.formModel.dateTo).then(function(res){
				vm.aggregatesByLanguageVeniceNoIt = res.data.results;
			});
		}

		var getByLanguage = function(){
			ApiAggregateService.GetByLanguage(vm.formModel.dateFrom, vm.formModel.dateTo).then(function(res){
				console.log(res.data.results);
				vm.aggregatesByLanguage = res.data.results;
			});
		}

		var getPlaceAggregates = function () {
			ApiAggregateService.GetPlaceAggregates(vm.formModel.dateFrom, vm.formModel.dateTo).then(function(res){
				vm.aggregatesByCountry = res.data.results.countries;
				vm.aggregatesByCity =res.data.results.cities;
				
			});
		}

		// var getByCountry = function(){
		// 	ApiAggregateService.GetByCountry().then(function(res){
		// 		console.log(res.data.results);
		// 		vm.aggregatesByCountry = res.data.results;
		// 	});
		// }


		// var getByCity = function(){
		// 	ApiAggregateService.GetByCity().then(function(res){
		// 		console.log(res.data.results);
		// 		vm.aggregatesByCity= res.data.results;
		// 	});
		// }		

		var getUserAggregates = function(){
			ApiAggregateService.GetUserAggregates(vm.formModel.dateFrom, vm.formModel.dateTo).then(function(res){
				vm.aggregatesByUserHighestRatio =  res.data.results.highest_ratio;
				vm.aggregatesByUserMostTweets = res.data.results.most_tweets;
				vm.aggregatesByUserMostFollowers = res.data.results.followers;
			});
		}

		// var getUsersWithHighestRatio = function(){
		// 	ApiAggregateService.GetUsersWithHighestRatio().then(function(res){
		// 		console.log(res.data.results);
		// 		vm.aggregatesByUserHighestRatio = res.data.results;
		// 	});
		// }


		// var getUsersWithMostTweets = function(){
		// 	ApiAggregateService.GetUsersWithMostTweets().then(function(res){
		// 		console.log(res.data.results);
		// 		vm.aggregatesByUserMostTweets = res.data.results;
		// 	});
		// }


		// var getUsersWithMostFollowers = function(){
		// 	ApiAggregateService.GetUsersWithMostFollowers().then(function(res){
		// 		console.log(res.data.results);
		// 		vm.aggregatesByUserMostFollowers = res.data.results;
		// 	});
		// }



		vm.increaseLimit = function(){
			vm.scopeLimit += 25;
		}

		vm.sanitize = function (term) {
			return $sce.trustAsHtml(term);
		}
	}

})();