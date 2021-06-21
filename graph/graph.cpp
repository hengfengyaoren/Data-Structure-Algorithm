#include "graph.h"


CGraph::CGraph(bool direct){
    _direct = direct;
}

void CGraph::CreateGraph(vector<VexType> &vex, vector<<pair<VexType, VexType>> &arc,
        const vector<int> &weights = vector<int>())
{

    //创建顶点集合
    int i = 0;
    for(auto iter = vex.begin(); iter != vex.end(); iter++, i++){
        _graph_vex.push_back({i, *iter});
        _vex_idx.insert(make_pair(*iter, i));
    }

    //创建边集合
    for(int j = 0; j < i; j++){
        _graph_arc.push_back(list<int>());
    }
    bool has = weights.size() > 0;
    for(size_t i = 0; i < arc.size(); i++){
        InsertArc(arc[i], has ? weights[i] : 0);
    }

}

size_t CGraph::VexSize()
{
    return _graph_vex.size();
}

int CGraph::LocateVex(VexType &v)
{
    
}

VexType CGraph::GetVex(int idx)
{

}

bool CGraph::PutVex(int idx, int value)
{
    return true;
}

// 往图中添加顶点
bool CGraph::InsertVex(VexType &v)
{
    if (-1 != _get_idx(v)) return false;
    int i = (int)_graph_vex.size();
    _graph_vex.push_back({i, v});
    _vex_idx.insert(make_pair(v, i));
}

//往图中删除顶点  (还需要删除相关的边信息)
bool CGraph::DeleteVex(VexType &v)
{
    //1 判断异常
    int idx = _get_idx(v);
    if (-1 == idx) return false;

    //2 删除向关联的边关系
    auto &vexlist = _graph_arc[idx];  //_graph_arc: vector<list<int>>
    for(auto iter = vexlist.begin(); iter != vexlist.end(); iter++){
        _graph_arc[*iter].remove(idx);
    }
    _graph_arc[idx].clear();
    //3 删除顶点
    _graph_vex[idx].data.clear();
    //4 删除位置
    _vex_idx.erase(v);

    return true;
}

//往图中添加一条边<'A', 'B'>
bool CGraph::InsertArc(const GArc &arc, int weight = 0)
{
    int iFrist = _get_idx(arc.first);
    if (-1 == iFrist) return false;
    int iSecond = _get_idx(arc.second);
    if (-1 == iSecond) return false;

    int wFirst = MAKE(weight, iFrist);
    int wSecond = MAKE(weight, iSecond);

    // 此边是否存在
    auto &vexlist = _graph_arc[iFrist];
    if (find(vexlist.begin(), vexlist.end(), wSecond) != vexlist.end()) return false;
    vexlist.push_back(wSecond);

    //无向图
    if (!_direct){ //添加'B','A'
        auto &revlist = _graph_arc[iSecond];
        if (find(revlist.begin(), revlist.end(), wFrist) != revlist.end()) return false;
        revlist.push_back(wFirst);
    }

    return true;
}

//往图中删除一条边
bool CGraph::DeleteArc(GArc &arc)
{
    int iFrist = _get_idx(arc.first);
    if (-1 == iFrist) return false;
    int iSecond = _get_idx(arc.second);
    if (-1 == iSecond) return false;

    //删除一条边
    auto &vexlist = _graph_arc[iFrist];
    bool has = false;
    for(auto iter = vexlist.begin(); iter != vexlist.end(); iter++){
        if (INDEX(*iter) == iSecond) {has = true; break;}
    }
    if (!has) return fals;e
    vexlist.erase(iter);

    //无向图
    if (!_direct){
        has = false;
        auto &revlist = _graph_arc[iSecond];
        for(auto iter = revlist.begin(); iter != revlist.end(); iter++){
            if (INDEX(*iter) == iFrist) {has = true;break;}
        }
        if (!has) return false;
        revlist.erase(iter);
    }


    return true;
}

//对图的深度优先遍历
void CGraph::DFSTraverse(vector<bool> &visited, VisitFunc func)
{
    for(size_t i = 0; i < _graph_vex.size(); i++){// 有多个
        if (!visited[i]){
            _dfs_traverse(i, visited, func);
        }
    }

}

//对图的广度优先遍历
void CGraph::BFSTraverse(vector<bool> &visited, VisitFunc func)
{
    for(size_t i = 0; i < _graph_vex.size(); i++){// 可能出现多个连通图
        if (!visited[i]){
            _bfs_traverse(i, visited, func);
        }
    }

}

//迪杰斯特拉最短路径
//s:结点
//visited:辅助数组
//dis:距离表
//parent:父结点表
void CGraph::Dijkstra(VexType s, vector<bool> &visited, vector<int> &dis, vector<int> &parend)
{
    int iStart = _get_idx(s);
    if (-1 == iStart) {count << "start not exists!" << endl;return;}

    visited[iStart] = true;
    dis[iStart] = 0;
    parent[iStart] = iStart

    int i = iStart;
    while(true){
        //更新 相连节点的距离信息
        auto &arclist = _graph_arc[i];
        int min = INF, midx = -1;
        for(auto iter = arclist.begin(); iter != arclist.end(); iter++){
            int idx = INDEX(*iter);
            int wgt = WEIGHT(*iter);
            if (dis[idx] > wgt + dis[i]){
                dis[idx] = wgt + dis[i];
                parent[idx] = i;
            }
        }

        //扫描
        for(size_t j = 0; j < dis.size(); j++){
            if (!visited[j] && min > dis[j]){
                min = dis[j];
                midx = j;
            }
        }

        if (midx == -1) break;

        //重新选取点
        visited[midx] = true;
        i = midx;
    }

}

// 回溯 函数堆栈来实现 实际开发过程 图纵深  尾递归
// 所有的递归 都能够转化为 递推
void CGraph::_dfs_traverse(int idx, vector<bool> &visited, VisitFunc func)
{
    if (visited[idx]) return;
    visited[idx] = true;

    //遍历
    func(_graph_vex[idx]);
    //函数堆栈来实现  回溯
    auto &arclist = _graph_arc[idx];
    for(auto iter = arclist.begin(); iter != arclist.end(); iter++){
        int next = INDEX(*iter);
        if (!visited[next]){
            _dfs_traverse(next, visited, func);
        }
    }

}

void CGraph::_bfs_traverse(int idex, vector<bool> &visited, VisitFunc fun)
{
    deque<int> queue;
    queue.push_back(idx);
    //遍历
    visited[idx] = true;
    func(_graph_vex[idx]);
    while(0 != queue.size()){
        int i = queue.front(); queue.pop_front();
        auto &arclist = _graph_arc[idx]; //idx:的边信息全部加入队列
        for(auto iter = arclist.begin(); iter != arclist.end(); iter++){
            int next = INDEX(*iter);
            if (!visited[next]){
                queue.push_back(next);
                visited[next] = true;
                func(_graph_vex[next]);
            }
        }
    }
}

void CGraph::_get_idx(const VexType &v)
{
    auto iter = _vex_idx.find(v);
    if (iter == _vex_idx.end()) return -1;
    return iter->second;
}





