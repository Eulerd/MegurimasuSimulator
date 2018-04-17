#pragma once
#include "Cell.h"
#include "Transform.h"

class Field
{
private:
	/// <summary>
	/// フィールド情報
	/// </summary>
	Grid<Cell> _cells;

	/// <summary>
	/// 領域ポイントを計算するとき探索したかを格納する
	/// </summary>
	Grid<bool> _status;

private:
	/// <summary>
	/// 囲まれている領域を探索する
	/// </summary>
	/// <param name="pos">探索を開始する座標</param>
	/// <param name="tile">どのタイルで囲まれているか</param>
	void dfsAreaPoint(Point pos, TileType tile);

public:
	/// <summary>
	/// フィールドを生成します
	/// </summary>
	/// <param name="file">フィールド情報のあるjsonファイル</param>
	/// <returns>生成したフィールド</returns>
	static Field Create(FilePath file);

	/// <summary>
	/// 指定のタイルで囲まれた領域の得点を計算します
	/// </summary>
	/// <param name="tile">どのタイルで囲まれているか</param>
	/// <returns>領域ポイント</returns>
	int GetAreaPoint(TileType tile);

	/// <summary>
	/// セル情報を取得する
	/// </summary>
	/// <returns>フィールドのセル情報</returns>
	Grid<Cell> GetCells() const;

	/// <summary>
	/// セルを塗る
	/// </summary>
	/// <param name="pos">塗るセルの座標</param>
	/// <param name="team">セルを塗るチーム</param>
	void PaintCell(Point pos, TeamType team);

	/// <summary>
	/// タイルを取る
	/// </summary>
	/// <param name="pos">タイルの座標</param>
	void RemoveTile(Point pos);

	/// <summary>
	/// 指定座標がフィールドの中であるか判定する
	/// </summary>
	/// <param name="pos">フィールド内か判定する座標</param>
	/// <returns>座標がフィールド内であるか</returns>
	bool IsInField(Point pos);

public:
	Field();

	void operator=(const Field& other);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="size">フィールドの大きさ</param>
	Field(Size size);

	/// <summary>
	/// セルを元にフィールドを生成するコンストラクタ
	/// </summary>
	/// <param name="cells">元となるセル</param>
	Field(Grid<Cell> cells);

	virtual ~Field();
};
