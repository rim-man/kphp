@ok
<?php
interface Barable {
  public function bar();
}
class Foo implements Barable {
  public function bar (){
  }
}

function factory(): Barable {
  return new Foo();
}

$foo = factory();
$foo->bar();
