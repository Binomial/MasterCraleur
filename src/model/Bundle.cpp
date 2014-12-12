
#include "../../header/model/Bundle.h"

Bundle::Bundle() {
    s_letter a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, joker;
    a.car = 'a';
    a.point = 1;
    e.car = 'e';
    e.point = 1;
    i.car = 'i';
    i.point = 1;
    n.car = 'n';
    n.point = 1;
    o.car = 'o';
    o.point = 1;
    r.car = 'r';
    r.point = 1;
    s.car = 's';
    s.point = 1;
    t.car = 't';
    t.point = 1;
    u.car = 'u';
    u.point = 1;
    l.car = 'l';
    l.point = 1;

    d.car = 'd';
    d.point = 2;
    m.car = 'm';
    m.point = 2;
    g.car = 'g';
    g.point = 2;

    b.car = 'b';
    b.point = 3;
    c.car = 'c';
    c.point = 3;
    p.car = 'p';
    p.point = 3;

    f.car = 'f';
    f.point = 4;
    h.car = 'h';
    h.point = 4;
    v.car = 'v';
    v.point = 4;

    j.car = 'j';
    j.point = 8;
    q.car = 'q';
    q.point = 8;

    k.car = 'k';
    k.point = 10;
    w.car = 'w';
    w.point = 10;
    x.car = 'x';
    x.point = 10;
    y.car = 'y';
    y.point = 10;
    z.car = 'z';
    z.point = 10;

    joker.car = '8';
    joker.point = 0;

    letters.push_back(joker);
    letters.push_back(joker);

    for(int i=0; i < 9; i++)
        letters.push_back(a);
    for(int i=0; i < 15; i++)
        letters.push_back(e);
    for(int j=0; j < 8; j++)
        letters.push_back(i);
    for(int i=0; i < 6; i++)
        letters.push_back(n);
    for(int i=0; i < 6; i++)
        letters.push_back(o);
    for(int i=0; i < 6; i++)
        letters.push_back(r);
    for(int i=0; i < 6; i++)
        letters.push_back(s);
    for(int i=0; i < 6; i++)
        letters.push_back(t);
    for(int i=0; i < 6; i++)
        letters.push_back(u);
    for(int i=0; i < 5; i++)
        letters.push_back(l);
    for(int i=0; i < 3; i++)
        letters.push_back(o);
    for(int i=0; i < 3; i++)
        letters.push_back(d);
    for(int i=0; i < 3; i++)
        letters.push_back(m);
    for(int i=0; i < 2; i++)
        letters.push_back(g);
    for(int i=0; i < 2; i++)
        letters.push_back(b);
    for(int i=0; i < 2; i++)
        letters.push_back(c);
    for(int i=0; i < 2; i++)
        letters.push_back(p);
    for(int i=0; i < 2; i++)
        letters.push_back(f);
    for(int i=0; i < 2; i++)
        letters.push_back(h);
    for(int i=0; i < 2; i++)
        letters.push_back(v);
    
    letters.push_back(j);
    letters.push_back(q);
    letters.push_back(k);
    letters.push_back(w);
    letters.push_back(x);
    letters.push_back(y);
    letters.push_back(z);
}

void Bundle::initBundle() {
    std::random_shuffle(letters.begin(), letters.end());
}

bool Bundle::isEmpty() {
    return letters.empty();
}

s_letter Bundle::takeLetter() {
    s_letter result;
    result = letters.at(letters.size()-1);
    letters.pop_back();
    return result;
}

