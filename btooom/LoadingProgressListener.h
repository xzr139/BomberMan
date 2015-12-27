#pragma once
#ifndef __LoadingProgressListener_H__
#define __LoadingProgressListener_H__

#include "ExampleApplication.h"
#include "BtooomFrameListener.h"
#include "Ogre.h"
class LoadingProgressListener :public ResourceGroupListener
{
public:

LoadingProgressListener(int& meter) :

m_progressMeter(meter){ m_currentResource = 0;}



// 资源组ResourceGroupListener事件方法



// 当资源组开始解析脚本的时候被调用

void resourceGroupScriptingStarted(const String& groupName,

size_t scriptCount){}



// 当一个脚本开始被解析的时候调用

void scriptParseStarted(const String& scriptName){}



// 当一个脚本已经被解析完的时候调用

void scriptParseEnded(){}



// 当资源组中脚本被解析完毕的时候被调用

void resourceGroupScriptingEnded(const String& groupName){}



// 当开始载入资源组中资源的时候被调用

void resourceGroupLoadStarted(const String& groupName,size_t resourceCount)

{ m_resCount = resourceCount;}



// 当开始载入一个资源的时候被调用

void resourceLoadStarted(const ResourcePtr& resource){}



// 当一个资源载入结束的时候被调用

void resourceLoadEnded();



// 当世界几何体开始载入的时候被调用

void worldGeometryStageStarted(const String& description){}



// 当世界地图载入结束的时候被调用

void worldGeometryStageEnded();



// 当资源组的资源全部载入结束的时候被调用

void resourceGroupLoadEnded(const String& groupName){}

private:

int m_resCount;

int m_currentResource;

int &m_progressMeter;

};

#endif