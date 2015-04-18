$e = $ '.e'
$p = $ '.p'
$q = $ '.q'
$zn = $ '.zn'
$d = $ '.d'
$pt = $ '.plain-text'
$ct = $ '.cipher-text'
$generateBtn = $ '.generate'


privateKey = null
clicking = false


encrypt = ->
  return unless privateKey?
  pt = $pt.val()
  return unless pt? and pt != ''

  $ct.val privateKey.encrypt pt


decrypt = ->
  return unless privateKey?
  ct = $ct.val()
  return unless ct? and ct != ''

  $pt.val privateKey.decrypt ct


$generateBtn.click (e) ->
  return if clicking
  clicking = true
  e.preventDefault()

  privateKey = generatePrivateKey()

  $d.val privateKey.d
  $p.val privateKey.p
  $q.val privateKey.q
  $zn.val privateKey.zn
  $e.val privateKey.publicKey.e
  encrypt()
  clicking = false


$pt.change encrypt

$ct.change decrypt
