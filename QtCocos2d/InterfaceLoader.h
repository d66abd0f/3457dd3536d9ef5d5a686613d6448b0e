#pragma once

#include <QString>
#include <QMap>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include "cocos2d.h"
#include "cocos-ext.h"
class NodeInfo;
class MetaInfo;

class MetaInfoBase : public cocos2d::Ref
{
public:
	virtual bool init(){ return true; }

	static NodeInfo* createNodeByJobj(const QJsonObject& jobj, MetaInfo* root);

	virtual bool readFromJObj(const QJsonObject& jobj, MetaInfo* root) = 0;
	void deselectAllRecursive();
	void setSelectingButtonVisibleRecursive();

protected:
	cocos2d::Vector<MetaInfoBase*> _children;
	cocos2d::extension::ControlButton* _selectingButton = nullptr;

	MetaInfo* _root = nullptr;
	bool _selectingMoved = false;
	cocos2d::Point _beginWorldPosition;
};

class MetaInfo : public MetaInfoBase
{
public:

	CREATE_FUNC(MetaInfo);
	virtual ~MetaInfo();

	bool loadFromFile(const QString& filename);
	cocos2d::Node* getBaseNode(){ return _baseNode; }

	virtual bool readFromJObj(const QJsonObject& jobj, MetaInfo* root);
protected:
	cocos2d::Node* _baseNode = nullptr;
	QString _fullFilename;

};

class NodeInfo : public MetaInfoBase
{
public:

	CREATE_FUNC(NodeInfo);
	virtual ~NodeInfo();

	cocos2d::Node* getNode() { return _node; }

	QVariant getCustomProperty(const QString& name, const QVariant& defaultVal);

	QString displayName;
	QString baseType;
	QString customClass;
	QMap<QString, QVariant> customProperties;

	virtual bool readFromJObj(const QJsonObject& jobj, MetaInfo* root);
protected:
	cocos2d::Node* _node = nullptr;

private:
	bool readNodeProperty(const QJsonObject& jobj);
	bool readCustomProperty(const QJsonArray& jarray);
	bool readChildren(const QJsonArray& jarray);

	bool readButtonProperty(const QJsonObject&jobj);

protected:
	bool onSelectingTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onSelectingTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onSelectingTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onSelectingTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
};

class InterfaceLoader
{
public:
	static InterfaceLoader& getInstance() { static InterfaceLoader instance; return instance; }

private:
	InterfaceLoader(){}
	virtual ~InterfaceLoader(){}
	InterfaceLoader(InterfaceLoader const&);
	void operator=(InterfaceLoader const&);

public:
	MetaInfo* loadJSon(const QString& filename);
}; 