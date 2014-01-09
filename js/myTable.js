function formatFloatNumber(num , digits)
{
	return num.toFixed(digits);
}

function getAllKeys(object)
{
	var keys = [];
	for(var key in object)
	{
		keys.push(key);
	}
	return keys;
}

function getClassName(elem_id)
{
	return $('#' + elem_id).attr('class')
}

function getAlltableElement(table_id)
{
	var arr = [];
	$("#" + table_id + "td").each(function(){
		arr[index] = $(this).html();
		index = index + 1;
	})
	return arr;
}

function insertElement(rows , table)
{
	for(var i = 0 ; i < rows.length ; i++)
	{
		var row = table.insertRow(-1);
		for(var j = 0 ; j < rows[i].length)
		{
			var col = row.insertCell(-1);
			col.innerHtml = rows[i][j];
		}
	}
}

function deleteAllElement(table)
{
	for(var i = table.rows.length - 1 ; i > 0 ; i--)
	{
		table.deleteRow(i);
	}
}

function test_deleteAllElement()
{
	var table = getElementById("tableId");
	deleteAllElement(table);
}
