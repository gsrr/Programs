from django.conf.urls import patterns, url
from rango import views

urlpatterns = patterns('',
        url(r'^$', views.index, name='index'),
        url(r'^about/', views.about, name='about'),
        url(r'^form_post/', views.index2, name='index2'),
        url(r'^about_post/', views.about_post, name='about_post'),
)
