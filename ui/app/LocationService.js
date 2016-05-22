(function(){
    'use strict';

	angular.module('SrcApp')
		.factory('LocationService', LocationService);


	function LocationService(){
	    var location = 'Timisoara';
	    var defaultDb = null;
	    var bounds = null;
	    var realtime = false;

	    var service = {
	        GetLocation: getLocation,
	        SetLocation: setLocation,
	        SetBounds: setBounds,
	        GetBounds: getBounds,
	        GetRealtime: getRealtime,
	        SetRealtime: setRealtime,
	        SetDefaultDb: setDefaultDb,
	        GetDefaultDb: getDefaultDb
	    };

	    return service;

        function setRealtime(val){
            realtime = val;
        }

        function setDefaultDb(val){
            if(val)
                defaultDb = val;
        }


        function getDefaultDb(){
            return defaultDb;
        }
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

	    function getRealtime(){
	        return realtime;
	    }
	}

})();