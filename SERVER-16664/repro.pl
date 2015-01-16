#!/usr/bin/env perl

#use DBI;
use IO::Uncompress::Bunzip2 qw(bunzip2 $Bunzip2Error);
use XML::Simple;

#use boolean;

use MongoDB;
use MongoDB::OID;
use File::Slurp;

my $limit = 500;

my $d = "part-0";
opendir(my $dh, $d) || die "Can't open XML directory";
my @filelist = readdir($dh);
closedir($dh);

foreach my $file (@filelist) {
  #print "Found: $file\n";
  next if ($file =~ /^\./);

  $path = "$d/$file";
  my $xml = read_file($path);

  my $xs = XML::Simple->new(
    KeyAttr    => '-name',
    ForceArray => [ 'test' ],
    ContentKey => '-value',
    NoSort     => 1
  );
  $test = $xs->XMLin ($xml);
  fix_scenario ($test);

  print "# Inserting to Mongo ($path).\n";
  my $conn = MongoDB::Connection->new;
  my $db = $conn->get_database ('xml');
  my $coll = $db->get_collection ('foo');
  my $x = $coll->insert($test);
  # print "# Done. ID: $x.\n";

}

#$DBH->disconnect;

sub fix_scenario {
  my $scenario = shift;
  # Move info message pairs to root.
  foreach (@{$scenario->{info_message}}) {
    $scenario->{$_->{name}} = $_->{value};
  }
  delete $scenario->{info_message} if (defined $scenario->{info_message});
  look_through_hash ($scenario);
}

sub look_through_hash {
  my $ref = shift;
  foreach my $key (keys %{$ref}){
    # Loop through hashes.
    if (ref($ref->{$key}) eq 'HASH') {
      look_through_hash ($ref->{$key});
    }
    # Loop through arrays.
    elsif (ref($ref->{$key}) eq 'ARRAY') {
      foreach my $array_element (@{$ref->{$key}}) {
        look_through_hash ($array_element);
      }
    }
    else {
      my $temp = $ref->{$key};
      # Booleans.
      $ref->{$key} = true  if ($temp eq 'yes');
      $ref->{$key} = false if ($temp eq 'no');

      # Integers and floaters.
      ##$ref->{$key} = $temp + 0   if ($temp =~ /^[0-9]+$/);
      ##$ref->{$key} = $temp + 0.0 if ($temp =~ /^[0-9]+\.[0-9]+$/);

      # Remove dots from keys for BSON.
      if ($key =~ /\./) {
        my $new_key = $key;
        $new_key =~ s/\.//g;
        $ref->{$new_key} = $ref->{$key};
        delete $ref->{$key};
      }
    }
  }
}
