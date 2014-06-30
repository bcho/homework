main = ->
  APP = Processing.getInstanceById 'app-canvas'
  NODES_COLLECTION = APP.getNC()
  NODES = NODES_COLLECTION.nodes

  $queryPeopleA = $ '#app-query-people-a'
  $queryPeopleB = $ '#app-query-people-b'
  $queryResult = $ '#app-query-result'

  # Returns list of names.
  getNames = ->
    nodesCount = NODES.size()
    return [] unless nodesCount > 0

    (NODES.get(i).name for i in [nodesCount - 1..0])

  # Returns list of nodes.
  getNodes = ->
    nodesCount = NODES.size()
    return [] unless nodesCount > 0
    (NODES.get(i) for i in [nodesCount - 1..0])

  # Query prompt control...

  containsName = (name) ->
    return name in getNames()

  window.checkRelationship = checkRelationship = ->
    aName = $queryPeopleA.val()
    bName = $queryPeopleB.val()

    if aName is ''
      $queryResult.text('请输入第一个查询名字')
      return
    if bName is ''
      $queryResult.text('请输入第二个查询名字')
      return

    if aName is bName
      $queryResult.text("#{aName} 和 #{bName} 是同一个人噢")
      return

    if not containsName aName
      $queryResult.text("#{aName} 不在亲戚列表中")
      return
    if not containsName bName
      $queryResult.text("#{bName} 不在亲戚列表中")

    if query(aName, bName)
      $queryResult.text("#{aName} 和 #{bName} 是亲戚关系")
    else
      $queryResult.text("#{aName} 和 #{bName} 不是亲戚关系")
  
  $queryPeopleA.keyup(checkRelationship)
  $queryPeopleB.keyup(checkRelationship)


  # Union find algorithm...
  
  prepareNodes = ->
    nodes = []
    for node, i in getNodes()
      nodes.push(
        name: node.name
        parent: i
        node: node
      )

    return nodes

  find = (a, nodes) ->
    a = nodes[a].parent while a != nodes[a].parent

    return a

  union = (a, b, nodes) ->
    aParent = find(a, nodes)
    bParent = find(b, nodes)

    nodes[aParent].parent = bParent

  # FIXME it's O(N^2)
  unionNodes = (nodes) ->
    for node, i in nodes
      for otherNode, j in nodes
        continue if i is j

        # Union this pair if they sit close enough.
        if node.node.isNear(otherNode.node)
          union(i, j, nodes)

    return nodes

  findIndexNodeByName = (name, nodes) ->
    for node, i in nodes
      return i if node.name is name
    return -1

  query = (aName, bName) ->
    nodes = unionNodes prepareNodes()

    aIndex = findIndexNodeByName(aName, nodes)
    return false if aIndex is -1
    bIndex = findIndexNodeByName(bName, nodes)
    return false if bIndex is -1
    
    return find(aIndex, nodes) is find(bIndex, nodes)

window.setTimeout(main, 500)
