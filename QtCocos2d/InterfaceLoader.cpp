#include "InterfaceLoader.h"
#include "cocos-ext.h"
#include <QJsonDocument>
#include <QFile>
#include <QtDebug>

USING_NS_CC;
USING_NS_CC_EXT;

MetaInfo* InterfaceLoader::loadJSon(const QString& filename)
{
	QString filenameStr = QString::fromStdString(FileUtils::getInstance()->fullPathForFilename(filename.toStdString()));
	qDebug() << filenameStr;
	MetaInfo * info = MetaInfo::create();
	if (!info->loadFromFile(filenameStr))
	{
		return nullptr;
	}
	return info;
}

bool MetaInfo::loadFromFile(const QString& filename)
{
	if (_baseNode)
	{
		return false;
	}

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;
	}
	QJsonParseError error;
	auto jdoc = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();

	_fullFilename = filename;

	_baseNode = Node::create();
	_baseNode->retain();

	return readFromJObj(jdoc.object(), this);
}

bool MetaInfo::readFromJObj(const QJsonObject& jobj, MetaInfo* root)
{
	auto jarray = jobj["SceneGraph"].toArray();
	for (int i = 0; i < jarray.count(); i++)
	{
		auto jobj = jarray[i].toObject();
		NodeInfo* node = createNodeByJobj(jobj, root);
		if (node)
		{
			_baseNode->addChild(node->getNode());
			_children.pushBack(node);
		}
	}
	_root = root;
	return true;
}

NodeInfo* MetaInfoBase::createNodeByJobj(const QJsonObject& jobj, MetaInfo* root)
{
	auto nodeinfo = NodeInfo::create();
	if (nodeinfo)
	{
		if (nodeinfo->readFromJObj(jobj, root))
		{
			return nodeinfo;
		}		
	}
	return nullptr;
}

void MetaInfoBase::deselectAllRecursive()
{
	if (_selectingButton)
	{
		_selectingButton->setSelected(false);
	}
	for (auto child : _children)
	{
		child->deselectAllRecursive();
	}
}

void MetaInfoBase::setSelectingButtonVisibleRecursive()
{
	if (_selectingButton)
	{
		_selectingButton->setVisible(false);
		for (auto child : _children)
		{
			child->setSelectingButtonVisibleRecursive();
		}
	}

}

MetaInfo::~MetaInfo()
{
	CC_SAFE_RELEASE_NULL(_baseNode);
}

/*
#define _SREAD(name)    name=jobj[#name].toString();
#define _IREAD(name)    name=jobj[#name].toInt();
#define _LREAD(name)    name=(qint64)jobj[#name].toDouble();
#define _FREAD(name)    name=(float)jobj[#name].toDouble();
*/
bool NodeInfo::readFromJObj(const QJsonObject& jobj, MetaInfo* root)
{
	if (_node)
	{
		return false;
	}

	displayName = jobj["Name"].toString();
	baseType = jobj["Type"].toString();
	customClass = jobj["CustomClass"].toString();

	qDebug() << baseType;

	if (baseType == "Button")
	{
		auto button = ControlButton::create();
		_node = button;
		readButtonProperty(jobj["ButtonProperty"].toObject());
	}

	if (_node)
	{
		_node->retain();
		if (!readNodeProperty(jobj["NodeProperty"].toObject()))
		{
			return false;
		}
		if (!readCustomProperty(jobj["CustomProperty"].toArray()))
		{
			return false;
		}
		if (!readChildren(jobj["Children"].toArray()))
		{
			return false;
		}

		//
		auto button = ControlButton::create();
//		button->setBackgroundSpriteForState(ui::Scale9Sprite::create("system/selecting.png"), Control::State::HIGH_LIGHTED);
		button->setBackgroundSpriteForState(ui::Scale9Sprite::create("system/selecting.png"), Control::State::SELECTED);
		button->setZoomOnTouchDown(false);
		Size contentSize = _node->getContentSize();
		Vec2 anchor = _node->getAnchorPoint();
		button->setPreferredSize(contentSize);
		button->setPosition((anchor.x)*contentSize.width, (anchor.y)*contentSize.height);
		_node->addChild(button);
		{
			auto touchListener = button->getTouchEventListener();
			touchListener->onTouchBegan = CC_CALLBACK_2(NodeInfo::onSelectingTouchBegan, this);
			touchListener->onTouchMoved = CC_CALLBACK_2(NodeInfo::onSelectingTouchMoved, this);
			touchListener->onTouchEnded = CC_CALLBACK_2(NodeInfo::onSelectingTouchEnded, this);
			touchListener->onTouchCancelled = CC_CALLBACK_2(NodeInfo::onSelectingTouchCancelled, this);
		}

		_selectingButton = button;

		_root = root;

		return true;
	}

	return false;
}


bool NodeInfo::readNodeProperty(const QJsonObject& jobj)
{
	if (!_node)
	{
		return false;
	}

	//////////////	Position	///////////////
	auto posArray = jobj["Position"].toArray();
	if (posArray.size() == 2)
	{
		Vec2 pos(posArray[0].toDouble(), posArray[1].toDouble());
		_node->setPosition(pos);
	}

	return true;
}

bool NodeInfo::readCustomProperty(const QJsonArray& jarray)
{
	return true;
}

bool NodeInfo::readChildren(const QJsonArray& jarray)
{
	// _children.pushBack
	// _root
	return true;
}

bool NodeInfo::readButtonProperty(const QJsonObject&jobj)
{
	if (!_node)
	{
		return false;
	}

	ControlButton *button = dynamic_cast<ControlButton *>(_node);
	if (!button)
	{
		return false;
	}

	QString normalImage = jobj["Normal"].toString();
	QString highLightedImage = jobj["HighLighted"].toString();
	QString disabledImage = jobj["Disabled"].toString();
	QString selectedImage = jobj["Selected"].toString();
	
	QString title = jobj["Title"].toString();

	if (!normalImage.isEmpty())
	{
		auto sprite = ui::Scale9Sprite::create(normalImage.toStdString());
		if (sprite)
		{
			button->setBackgroundSpriteForState(sprite, Control::State::NORMAL);
			button->setPreferredSize(sprite->getOriginalSize());
		}
	}
	if (!highLightedImage.isEmpty())
	{
		auto sprite = ui::Scale9Sprite::create(highLightedImage.toStdString());
		if (sprite)
		{
			button->setBackgroundSpriteForState(sprite, Control::State::HIGH_LIGHTED);
		}
	}
	if (!disabledImage.isEmpty())
	{
		auto sprite = ui::Scale9Sprite::create(disabledImage.toStdString());
		if (sprite)
		{
			button->setBackgroundSpriteForState(sprite, Control::State::DISABLED);
		}
	}
	if (!selectedImage.isEmpty())
	{
		auto sprite = ui::Scale9Sprite::create(selectedImage.toStdString());
		if (sprite)
		{
			button->setBackgroundSpriteForState(sprite, Control::State::SELECTED);
		}
	}

	if (!title.isEmpty())
	{
		button->setTitleLabelForState(Label::createWithSystemFont(title.toStdString(), "MS Gothic", 12), Control::State::NORMAL);
	}

	return true;
}

NodeInfo::~NodeInfo()
{
	CC_SAFE_RELEASE_NULL(_node);
}

bool NodeInfo::onSelectingTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (!_selectingButton || !_node)
	{
		return false;
	}
	// if control not pressed
	_root->deselectAllRecursive();
	if (_selectingButton->onTouchBegan(touch, event))
	{
		_selectingMoved = false;
		_beginWorldPosition = _node->getParent()->convertToWorldSpace(_node->getPosition());
		_selectingButton->setSelected(true);
		return true;
	}
	return false;
}

void NodeInfo::onSelectingTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (!_selectingButton || !_node)
	{
		return;
	}
	_selectingButton->onTouchMoved(touch, event);
	_selectingButton->setSelected(true);
	if (fabsf(touch->getLocation().x - touch->getStartLocation().x) < 1.0f
		&& fabsf(touch->getLocation().y - touch->getStartLocation().y) < 1.0f)
	{
		if (!_selectingMoved)
		{
			return;
		}
	}
	else
	{
		_selectingMoved = true;
	}

	Point moved = touch->getLocation() - touch->getStartLocation();
	_node->setPosition(_node->getParent()->convertToNodeSpace(_beginWorldPosition + moved));
}

void NodeInfo::onSelectingTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_selectingMoved = false;
	if (!_selectingButton || !_node)
	{
		return;
	}
	_selectingButton->onTouchEnded(touch, event);
	_selectingButton->setSelected(true);
}

void NodeInfo::onSelectingTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
	_selectingMoved = false;
	if (!_selectingButton || !_node)
	{
		return;
	}
	_selectingButton->onTouchCancelled(touch, event);
	_selectingButton->setSelected(true);
}
