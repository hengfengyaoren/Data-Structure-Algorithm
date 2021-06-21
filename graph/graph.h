#ifndef __GRAPH_H_
#define __GRAPH_H_

#define INF 0x7F7F7F7F

// 16  前8位存储权重信息 | 后8位存储索引
#define WEIGHT(i) ((i&0xff00)>>8)
#define INDEX(i) (i&0xff)
#define MAKE(w, i) (((w)&0xff)<<8) | i)

typedef vector<list<int>> GraphArc;  //边集合
typedef string VexType;
typedef struct Vex{
    int idx;        //顶点索引
    VexType data;   //顶点信息  实际工程中一般是指针
}GVex;

typedef pair<VexType, VexType> GArc;

typedef bool (*VisitFunc)(GVex &vex);  //遍历函数

typedef vector< GVex > GraphVex;       //顶点集合

class CGraph{
public:
    CGraph(bool direct = true);

    //创建图接口
    void CreateGraph(vector<VexType> &vex, vector<<pair<VexType, VexType>> &arc,
        const vector<int> &weights = vector<int>());

    //顶点的大小
    inline size_t VexSize(){return _graph_vex.size();}
    //根据顶点信息查找位置
    int LocateVex(VexType &v);
    //根据位置查找顶点信息
    VexType GetVex(int idx);
    //修改idx的顶点的值
    bool PutVex(int idx, int value);

    // 往图中添加顶点
    bool InsertVex(VexType &v);
    //往图中删除顶点  (还需要删除相关的边信息)
    bool DeleteVex(VexType &v);
    //往图中添加一条边<'A', 'B'>
    bool InsertArc(const GArc &arc, int weight = 0);
    //往图中删除一条边
    bool DeleteArc(GArc &arc);

    //对图的深度优先遍历
    void DFSTraverse(vector<bool> &visited, VisitFunc func);
    //对图的广度优先遍历
    void BFSTraverse(vector<bool> &visited, VisitFunc func);
    //迪杰斯特拉最短路径
    void Dijkstra(VexType s, vector<bool> &visited, vector<int> &dis, vector<int> &parend);

private:

    int _get_idx(const VexType &v);


private:
    GraphArc    _graph_arc;     //边集合信息
    GraphVex    _graph_vex;     //顶点集合信息

    map<VexType, int> _vex_idx; //数据对应  idx
    bool    _direct;            //是否有向图
};



#endif //__GRAPH_H_
