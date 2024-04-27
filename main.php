<?php
$t = time();

class event_t {
  public $type;
  public $time;
}

function event_loop() {
  static $prev_time = 0;
  global $t;
  $now = time();

  if ($now != $prev_time) {
    $prev_time = $now;

    return (object) array(
      'type' => 6,
      'time' => $now
    );
  }

  return (object) array(
    'type' => 0
  );
}

function local_time() {
  global $t;
  echo "\x1B[1;1H\x1B[?25h";

  $dt = new DateTime("@$t");
  $buffer = $dt->format("d M Y, H:i:s");
  echo $buffer;
  flush();
}

$time_loop = 1;
$stop = 0;

while (!$stop) {
  $event = event_loop();

  if ($event->type) {
    if ($event->type == 6) {
      $t = $event->time;
      $time_loop = 1;
    }
  }

  if ($time_loop) {
    local_time();
    $time_loop = 0;
  }
}
?>
