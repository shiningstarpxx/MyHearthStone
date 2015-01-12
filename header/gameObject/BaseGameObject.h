
#ifndef BASEGAMEOBJECT_H_
#define BASEGAMEOBJECT_H_

class Game;
class EntityObject;

class BaseGameObject {
	Game &game;
protected:
	EntityObject *parent;
	Game& getGame() {
		return game;
	}
public:
	BaseGameObject(Game &g, EntityObject *p) :
			game(g), parent(p) {
	}
	// 是否可读（未调用）
	virtual bool canRead() = 0;
	// 打印该对象
	virtual void show(bool detail) = 0;
	// 获得该对象的描述
	virtual string getDesc(bool detail) = 0;
};

#endif /* BASEGAMEOBJECT_H_ */
