set data [gets stdin]
scan $data "%d %d" N k
set ns  [new Simulator]
$ns rtproto DV
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam
    exit 0
}

$ns color 0 red
$ns color 3 orange
$ns color 2 purple
$ns color 1 blue
$ns color 4 green
$ns color 5 brown
$ns color 6 BlueViolet
$ns color 8 cyan
$ns color 10 grey
$ns color 11 snow
$ns color 7 aqua
$ns color 9 azure

for {set i 0} {$i < $N} {incr i} {
	set n($i) [$ns node]
}

for {set i 0} {$i < $N} {incr i} {
	$ns duplex-link $n($i) $n([expr ($i + 1) % $N]) 512Kb 5ms DropTail
}

for {set i 0} {$i < $k} {incr i} {
	set input [gets stdin]
	scan $input "%d %d" u v
	set tcp [new Agent/TCP]
	$ns attach-agent $n($u) $tcp
	$tcp set class_ $i
	set sink [new Agent/TCPSink]
	$ns attach-agent $n($v) $sink
	$ns connect $tcp $sink
	set ftp0 [new Application/FTP]
	$ftp0 attach-agent $tcp
	$ns at 0.1 "$ftp0 start"
	$ns at 1.5 "$ftp0 stop"
}

$ns at 2.0 "finish"
$ns run
