function setSelectItem(item , elemId)
{
	$("#" + elemId + " option").each(function(){
		if($(this).html() == item)
		{
			$(this).attr("selected" , true);
		}
	});
}

function path_removeLastPart(str)
{
	return str.substring(0,str.lastindexOf("/"));
}

function joinArray(arr , delimit)
{
	return arr.join(delimit);
}

function setElementDependency(items , dependency)
{
	for(var i = 0 ; i < items.length ; i++)
	{
		$("#" + items[i]).addClass(dependency);
	}
}

function checkNumber(str)
{
	var patternNumber = /^[0-9]+$/;
	if(str == "")
	{
		return false;
	}
	else if(!patternNumber.test(str))
	{
		return false;
	}
	return true;
}

function browseArray(arr)
{
        $.each(arr , function(index , value){
                console.log(index + ":" + value);
        })
}

function browseObject(obj)
{
        $.each(obj , function(key , value){
                console.log(key + ":" + value);
        })
}
