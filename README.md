# FolderModelTest
QFileSystemModel と QSortFilterProxyModel を組み合わせた FolderModel のテストプログラム。
![Screen shot](https://user-images.githubusercontent.com/2529849/39419708-12f24682-4c9c-11e8-9095-414d5d2b00c3.png)

# ポイント
* QSortFilterProxyModel を継承した FolderModel を定義。
* QFileSystemModel のインスタンスをメンバ変数 fsModel_ として持たせ、QFileSystemModel のメソッドはそのまま　FolderModel のメソッドとして再定義。
* 外部から渡される QModelIndex は QSortFilterProxyModel 用なので、QFileSystemModel で使用する際は mapToSource() で変換。
* QFileSystemModel から返された QModelIndex を戻り値として返す場合は、mapFromSource() で変換してから返す。

# フィルタ
* フィルタは QSortFilterProxyModel の機能は使用せず、QFileSystemModel の機能をそのまま使用している。

# ソート
* ソートの比較処理は lessThan() を override して再定義している。
** ソート条件はメンバ変数 sortFlags_、sortOrder_、dotFirst_ に設定されている。
** dorFirst_ == true であれば、どのようなソート条件であっても、必ず "." ".." を先頭に持ってくる
