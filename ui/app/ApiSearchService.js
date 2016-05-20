(function () {
	'use strict';

	angular.module('SrcApp')
		.factory('ApiAggregateService', ApiAggregateService);

	ApiAggregateService.$inject = ['$q', '$http'];
	function ApiAggregateService($q, $http){
		var baseUrl = '/api/aggregate/'
		var service = {
			GetByLanguageVeniceTweetsNoIt: getByLanguageVeniceTweetsNoIt,
			GetByLanguage: getByLanguage,
			GetPlaceAggregates: getPlaceAggregates,
			GetUserAggregates: getUserAggregates,
			GetHashtagOccurences: getHashtagOccurences
		};

		return service;

		function buildDatePartOfQuery(date_from, date_to){
			if((angular.isDefined(date_from) && angular.isDefined(date_to)) && date_from !== '' && date_to !== ''){
				return date_from + '/' + date_to
			}
			return null + '/' + null;
		}

		function getByLanguageVeniceTweetsNoIt(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_by_language_no_it/' + buildDatePartOfQuery(date_from, date_to)
			});
		}

		function getByLanguage(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_by_language/' +  buildDatePartOfQuery(date_from, date_to)
			});
		}


		function getByCountry(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_by_country/' +  buildDatePartOfQuery(date_from, date_to)
			});
		}


		function getByCity(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_by_city/' +  buildDatePartOfQuery(date_from, date_to)
			});
		}


		function getUserAggregates(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_user_aggregates/' + buildDatePartOfQuery(date_from, date_to)
			})
		}

		function getHashtagOccurences(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_hashtag_occurences/' + buildDatePartOfQuery(date_from, date_to)
			})
		}

		function getPlaceAggregates(date_from, date_to){
			return $http({
				method: 'GET',
				url: baseUrl + 'get_by_places/' + buildDatePartOfQuery(date_from, date_to)
			}) 
		}

		// function getUsersWithHighestRatio(date_from, date_to){
		// 	return $http({
		// 		method: 'GET',
		// 		url: baseUrl + 'get_user_highest_ratio/' + buildDatePartOfQuery(date_from, date_to)
		// 	})
		// }

		// function getUsersWithMostTweets(date_from, date_to){
		// 	return $http({
		// 		method: 'GET',
		// 		url: baseUrl + 'get_user_most_tweets/' + buildDatePartOfQuery(date_from, date_to)
		// 	})
		// }

		// function getUsersWithMostFollowers(date_from, date_to){
		// 	return $http({
		// 		method: 'GET',
		// 		url: baseUrl + 'get_user_most_followers/' + buildDatePartOfQuery(date_from, date_to)
		// 	})
		// }

	}

})();
