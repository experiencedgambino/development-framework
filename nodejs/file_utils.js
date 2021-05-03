const dirTree = require("directory-tree");

exports.myDateTime = function () {
  return Date();
};


exports.GetFilesInDirectory = function (dir) {
  var tree = dirTree(dir)
  var arr = []

  for (var i = 0; i < tree.children.length; i++) {
    if (tree.children[i].type == 'file') {
      arr.push(tree.children[i].name)
    }
  }
  
  return arr;
};
