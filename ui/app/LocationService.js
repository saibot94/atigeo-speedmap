(function(){
    'use strict';

	angular.module('SrcApp')
		.factory('LocationService', LocationService);


	function LocationService(){
	    var location = 'Timisoara';
	    var bounds = null;
	    var service = {
	        GetLocation: getLocation,
	        SetLocation: setLocation,
	        SetBounds: setBounds,
	        GetBounds: getBounds
	    };

	    return service;


	    function setLocation(loc){
            location = loc;

	    }

	    function getLocation(){
	        return location;
	    }

	    function setBounds(bd){
	        bounds = bd;
	    }

	    function getBounds(){
	        return bounds;
	    }
	}

})();