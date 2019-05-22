#pragma once

// 顶点结构体
typedef struct Vertex {
	int row;	// 行号
	int col;	// 列号
	int info;	// 信息
}Vertex;

const int BLANK = -1;		// 空白
const int MAX_ROW = 4;		// 行数 10
const int MAX_COL = 4;		// 列数 16
const int MAX_PICNUM = 4;	// 图片种类数 20