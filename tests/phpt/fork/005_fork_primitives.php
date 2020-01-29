@ok
<?php

require_once 'polyfills.php';

function return_int() {
  sched_yield();
  return 5;
}

function return_double() {
  sched_yield();
  return 5.0;
}

function return_string() {
  sched_yield();
  return "abc";
}

function return_array_int() {
  sched_yield();
  return [1, 2, 3];
}

function return_array_string() {
  sched_yield();
  return ["a", "b", "c"];
}

function return_int_or_double($x) {
  if ($x) {
    return (float)return_int();
  } else {
    return return_double();
  }
}

function return_mixed_array($x) {
  if ($x) {
    return return_array_int();
  } else {
    return return_array_string();
  }
}

function return_var($x) {
  switch($x) {
    case 0: return return_int();
    case 1: return return_double();
    case 2: return return_string();
    case 3: return return_array_int();
    case 4: return return_array_string();
    case 5: return return_int_or_double(0);
    case 6: return return_int_or_double(1);
    case 7: return return_mixed_array(0);
    case 8: return return_mixed_array(1);
  }
  return false;
}


var_dump(wait_result(fork(return_int())));
var_dump(wait_result(fork(return_double())));
var_dump(wait_result(fork(return_string())));
var_dump(wait_result(fork(return_array_int())));
var_dump(wait_result(fork(return_array_string())));
for ($i = 0; $i < 2; $i++) {
  var_dump(wait_result(fork(return_int_or_double($i))));
  var_dump(wait_result(fork(return_mixed_array($i))));
}
for ($i = 0; $i < 10; $i++) {
  var_dump(wait_result(fork(return_var($i))));
}

$qs = [];
$qs[] = fork(return_int());
$qs[] = fork(return_double());
$qs[] = fork(return_string());
$qs[] = fork(return_array_int());
$qs[] = fork(return_array_string());
for ($i = 0; $i < 2; $i++) {
  $qs[] = fork(return_int_or_double($i));
  $qs[] = fork(return_mixed_array($i));
}
for ($i = 0; $i < 10; $i++) {
  $qs[] = fork(return_var($i));
}

foreach ($qs as $q) {
  var_dump(wait_result($q));
}