function setElementDependency(items , dependency)
{
	for(var i = 0 ; i < items.length ; i++)
	{
		$("#" + items[i]).addClass(dependency);
	}
}
