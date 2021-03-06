// Generated by CoffeeScript 1.7.1
(function() {
  var main,
    __indexOf = [].indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  main = function() {
    var $queryPeopleA, $queryPeopleB, $queryResult, APP, NODES, NODES_COLLECTION, checkRelationship, containsName, find, findIndexNodeByName, getNames, getNodes, prepareNodes, query, union, unionNodes;
    APP = Processing.getInstanceById('app-canvas');
    NODES_COLLECTION = APP.getNC();
    NODES = NODES_COLLECTION.nodes;
    $queryPeopleA = $('#app-query-people-a');
    $queryPeopleB = $('#app-query-people-b');
    $queryResult = $('#app-query-result');
    getNames = function() {
      var i, nodesCount, _i, _ref, _results;
      nodesCount = NODES.size();
      if (!(nodesCount > 0)) {
        return [];
      }
      _results = [];
      for (i = _i = _ref = nodesCount - 1; _ref <= 0 ? _i <= 0 : _i >= 0; i = _ref <= 0 ? ++_i : --_i) {
        _results.push(NODES.get(i).name);
      }
      return _results;
    };
    getNodes = function() {
      var i, nodesCount, _i, _ref, _results;
      nodesCount = NODES.size();
      if (!(nodesCount > 0)) {
        return [];
      }
      _results = [];
      for (i = _i = _ref = nodesCount - 1; _ref <= 0 ? _i <= 0 : _i >= 0; i = _ref <= 0 ? ++_i : --_i) {
        _results.push(NODES.get(i));
      }
      return _results;
    };
    containsName = function(name) {
      return __indexOf.call(getNames(), name) >= 0;
    };
    window.checkRelationship = checkRelationship = function() {
      var aName, bName;
      aName = $queryPeopleA.val();
      bName = $queryPeopleB.val();
      if (aName === '') {
        $queryResult.text('请输入第一个查询名字');
        return;
      }
      if (bName === '') {
        $queryResult.text('请输入第二个查询名字');
        return;
      }
      if (aName === bName) {
        $queryResult.text("" + aName + " 和 " + bName + " 是同一个人噢");
        return;
      }
      if (!containsName(aName)) {
        $queryResult.text("" + aName + " 不在亲戚列表中");
        return;
      }
      if (!containsName(bName)) {
        $queryResult.text("" + bName + " 不在亲戚列表中");
      }
      if (query(aName, bName)) {
        return $queryResult.text("" + aName + " 和 " + bName + " 是亲戚关系");
      } else {
        return $queryResult.text("" + aName + " 和 " + bName + " 不是亲戚关系");
      }
    };
    $queryPeopleA.keyup(checkRelationship);
    $queryPeopleB.keyup(checkRelationship);
    prepareNodes = function() {
      var i, node, nodes, _i, _len, _ref;
      nodes = [];
      _ref = getNodes();
      for (i = _i = 0, _len = _ref.length; _i < _len; i = ++_i) {
        node = _ref[i];
        nodes.push({
          name: node.name,
          parent: i,
          node: node
        });
      }
      return nodes;
    };
    find = function(a, nodes) {
      while (a !== nodes[a].parent) {
        a = nodes[a].parent;
      }
      return a;
    };
    union = function(a, b, nodes) {
      var aParent, bParent;
      aParent = find(a, nodes);
      bParent = find(b, nodes);
      return nodes[aParent].parent = bParent;
    };
    unionNodes = function(nodes) {
      var i, j, node, otherNode, _i, _j, _len, _len1;
      for (i = _i = 0, _len = nodes.length; _i < _len; i = ++_i) {
        node = nodes[i];
        for (j = _j = 0, _len1 = nodes.length; _j < _len1; j = ++_j) {
          otherNode = nodes[j];
          if (i === j) {
            continue;
          }
          if (node.node.isNear(otherNode.node)) {
            union(i, j, nodes);
          }
        }
      }
      return nodes;
    };
    findIndexNodeByName = function(name, nodes) {
      var i, node, _i, _len;
      for (i = _i = 0, _len = nodes.length; _i < _len; i = ++_i) {
        node = nodes[i];
        if (node.name === name) {
          return i;
        }
      }
      return -1;
    };
    return query = function(aName, bName) {
      var aIndex, bIndex, nodes;
      nodes = unionNodes(prepareNodes());
      aIndex = findIndexNodeByName(aName, nodes);
      if (aIndex === -1) {
        return false;
      }
      bIndex = findIndexNodeByName(bName, nodes);
      if (bIndex === -1) {
        return false;
      }
      return find(aIndex, nodes) === find(bIndex, nodes);
    };
  };

  window.setTimeout(main, 500);

}).call(this);

//# sourceMappingURL=app.map
