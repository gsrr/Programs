from django.shortcuts import render

# Create your views here.

from django.http import HttpResponse


def about_post(request):
    ua = request.META["HTTP_USER_AGENT"]
    values = request.META.items()
    return HttpResponse("%s"%(str(request.POST['q'])))
    #return HttpResponse("Rango , Hello World!!")

def about(request):
    ua = request.META["HTTP_USER_AGENT"]
    values = request.META.items()
    return HttpResponse("%s"%(str(request.GET['q'])))
    #return HttpResponse("Rango , Hello World!!")

from django.template import RequestContext
from django.shortcuts import render_to_response

def index2(request):
    context = RequestContext(request)
    context_dict = {'boldmessage': "I am bold font from the context"}
    return render_to_response('rango/form_post.html', context_dict, context)

def index(request):
    context = RequestContext(request)
    context_dict = {'boldmessage': "I am bold font from the context"}
    return render_to_response('rango/index.html', context_dict, context)

