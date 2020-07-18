# t-pot: DirectX 12 の学習

となる予定

[公開ページ](http://t-pot.com/study_dx12/)

# 更新方法
- hugo で更新
- develop ブランチに push
- GitHub Actions がhugoのビルドをして、docsフォルダを作って、masterブランチにpushしてくれる
- GitHub Pages の機能で、masterブランチのdocsフォルダ以下がホームページに公開されます。

[![Actions Status](https://github.com/t-pot/study_dx12/workflows/build_web_site/badge.svg)](https://github.com/t-pot/study_dx12/actions)

# フォルダ構成
- src: 紹介しているソースコード
- docs: ホームページ（masterのみ、ビルド後）
- web_site: ビルド前のホームページ
- .github/workflows: GitHub Actions (CI) の設定ファイル
- .gitignore, .gitmodules: ファイル管理の設定
- README.md: このファイル
