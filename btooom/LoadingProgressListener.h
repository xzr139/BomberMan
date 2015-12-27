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



// ��Դ��ResourceGroupListener�¼�����



// ����Դ�鿪ʼ�����ű���ʱ�򱻵���

void resourceGroupScriptingStarted(const String& groupName,

size_t scriptCount){}



// ��һ���ű���ʼ��������ʱ�����

void scriptParseStarted(const String& scriptName){}



// ��һ���ű��Ѿ����������ʱ�����

void scriptParseEnded(){}



// ����Դ���нű���������ϵ�ʱ�򱻵���

void resourceGroupScriptingEnded(const String& groupName){}



// ����ʼ������Դ������Դ��ʱ�򱻵���

void resourceGroupLoadStarted(const String& groupName,size_t resourceCount)

{ m_resCount = resourceCount;}



// ����ʼ����һ����Դ��ʱ�򱻵���

void resourceLoadStarted(const ResourcePtr& resource){}



// ��һ����Դ���������ʱ�򱻵���

void resourceLoadEnded();



// �����缸���忪ʼ�����ʱ�򱻵���

void worldGeometryStageStarted(const String& description){}



// �������ͼ���������ʱ�򱻵���

void worldGeometryStageEnded();



// ����Դ�����Դȫ�����������ʱ�򱻵���

void resourceGroupLoadEnded(const String& groupName){}

private:

int m_resCount;

int m_currentResource;

int &m_progressMeter;

};

#endif