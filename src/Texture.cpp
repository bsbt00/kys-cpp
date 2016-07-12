#include "Texture.h"
#include "File.h"

Texture Texture::tm;

Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::copyTexture(const std::string& path, int num, int x, int y)
{
	if (num < 0) return;
	auto engine = Engine::getInstance();
	auto &v = tm.map[path.c_str()];
	if (v.size() == 0)
	{
		unsigned char* s;
		int l = 0;
		File::readFile((path + "/index.ka").c_str(), &s, &l);
		if (l == 0)return;
		l /= 4;
		v.resize(l);
		for (int i = 0; i < l; i++)
		{
			v[i].dx = *(short*)(s + i * 4);
			v[i].dy = *(short*)(s + i * 4 + 2);
		}
		delete s;
	}
	auto &t = v[num];
	if (!t.loaded)
	{
		t.tex = engine->loadImage(path + "/" + to_string(num) + ".png");
		if (!t.tex)
			t.tex = engine->loadImage(path + "/" + to_string(num) + "_0.png");
		engine->queryTexture(t.tex, &t.w, &t.h);
		t.loaded = true;
	}
	engine->renderCopy(t.tex, x - t.dx, y - t.dy, t.w, t.h);
}
