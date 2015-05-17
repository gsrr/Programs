#!/bin/bash




case $1 in
'get')
	curl -XGET 'http://localhost:9200/movies/movie/1' -d'{}'
	echo ""
	;;
'setsim')
	curl -XPOST 'http://localhost:9200/myindex/' -d '
	{"settings":{
		"similarity":
		{
			"newSimilarity":
			{
				"type":"default"
			}
		}
		    }
	}'
	echo ""
	;;
'setsim2')
	curl -XPOST 'http://localhost:9200/myindex2/' -d '
	{
		"settings":{
			"similarity": "BM25"
		}
	}'
	echo ""
	;;
'ic')
	curl -XGET 'http://localhost:9200/myindex/' -d'{}'	
	echo ""
	curl -XGET 'http://localhost:9200/movies/' -d'{}'	
	echo ""
	;;
'index')
	curl -XPUT "http://localhost:9200/movies/movie/1" -d'
	{
		"title": "The Godfather",
		"director": "Francis Ford Coppola",
		"year": 1972,
		"genres": ["Crime", "Drama"]
	}'
	;;
'search')
	curl -XPOST "http://localhost:9200/_search" -d'
	{
		"query": {
			"match_all": {}
		}
	}'
	;;
'chsim')
	curl -XPOST "http://localhost:9200/myindex/" -d'
	{
	  "mappings": {
	    "similarity": {
	      "newSimilarity": {
		"type": "default"
	      }
            }
	  }
	}'
	;;
'setting')
	curl -XGET 'http://localhost:9200/myindex/_settings'
	;;
'close')
	curl -XPOST 'localhost:9200/myindex/_close'
	;;
'open')
	curl -XPOST 'localhost:9200/myindex/_open'
	;;
'scroll')
	curl -XGET http://localhost:9200/movies/_search?search_type=scan&scroll=1m&size=10
	;;
'ss')
	curl -XGET http://localhost:9200/movies/_search?scroll=1m&search_type=scan&size=10
	;;
*)
	;;
esac
