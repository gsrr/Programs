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
