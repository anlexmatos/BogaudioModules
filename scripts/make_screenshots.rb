#!/usr/bin/env ruby

# To reggenerate README screenshots:
#  1. rm -rf ../../screenshots/Bogaudio/
#  2. (cd ../.. && ./Rack -d -t 1 Bogaudio)
#  3. ./scripts/make_screenshots.rb ../../screenshots/Bogaudio

screens = [
  {
    file: 'modules1.png',
    crop: false,
    rows: [
      ['VCO', 'LVCO', 'Sine', 'Pulse', 'XCO', 'Additator', 'FMOp'],
      ['LFO', 'LLFO', 'EightFO']
    ]
  },
  {
    file: 'modules2.png',
    crop: false,
    rows: [
      ['VCF', 'LVCF', 'FFB', 'EQ', 'EQS'],
      ['PEQ', 'PEQ6', 'PEQ6XF', 'PEQ14', 'PEQ14XF'],
      ['DADSRH', 'DADSRHPlus', 'Shaper', 'ShaperPlus', 'AD', 'ASR', 'ADSR', 'Follow', 'DGate', 'Edge']
    ]
  },
  {
    file: 'modules3.png',
    crop: false,
    rows: [
      ['Mix8', 'Mix8x', 'Mute8'],
      ['Mix4', 'Mix4x', 'Mix1', 'Mix2', 'VCM', 'Pan', 'XFade'],
      ['UMix', 'Mumix', 'Matrix44', 'Matrix88'],
      ['Switch44', 'Switch88', 'Switch1616']
    ]
  },
  {
    file: 'modules4.png',
    crop: false,
    rows: [
      ['VCA', 'VCAmp', '-', 'AMRM', 'Pressor', 'Lmtr', 'Nsgt', 'CmpDist'],
      ['Noise', 'SampleHold', 'Walk2', 'Walk', '-', 'EightOne', 'OneEight', 'AddrSeq', 'PGMR', 'PGMRX'],
      ['VU', 'Analyzer', 'AnalyzerXL']
    ]
  },
  {
    file: 'modules5.png',
    crop: false,
    rows: [
      ['Mono', 'Arp', 'Assign', 'Unison', 'PolyCon', 'PolyCon8', 'PolyOff16', 'PolyOff8', 'PolyMult', '-', 'Detune', 'Stack', 'Reftone'],
      ['Bool', 'Cmp', 'CVD', 'FlipFlop', 'Inv', 'Manual', 'FourMan', 'Mult', 'Offset', 'Slew', 'Sums', 'Switch', '-', 'Blank3', 'Blank6']
    ]
  },

  {
    file: 'oscillators1.png',
    crop: true,
    rows: [
      ['VCO', 'LVCO', 'Sine', 'Pulse', 'XCO']
    ]
  },
  {
    file: 'oscillators2.png',
    crop: true,
    rows: [
      ['Additator', 'FMOp']
    ]
  },
  {
    file: 'lfos.png',
    crop: true,
    rows: [
      ['LFO', 'LLFO', 'EightFO']
    ]
  },
  {
    file: 'filters.png',
    crop: true,
    rows: [
      ['VCF', 'LVCF', 'FFB', 'EQ', 'EQS']
    ]
  },
  {
    file: 'parametric_eqs.png',
    crop: true,
    rows: [
      ['PEQ', 'PEQ6', 'PEQ6XF', 'PEQ14', 'PEQ14XF']
    ]
  },
  {
    file: 'envelopes1.png',
    crop: true,
    rows: [
      ['DADSRH', 'DADSRHPlus']
    ]
  },
  {
    file: 'envelopes2.png',
    crop: true,
    rows: [
      ['Shaper', 'ShaperPlus', 'AD', 'ASR', 'ADSR', 'Follow']
    ]
  },
  {
    file: 'envelopes3.png',
    crop: true,
    rows: [
      ['DGate', 'Edge']
    ]
  },
  {
    file: 'noise.png',
    crop: true,
    rows: [
      ['Noise', 'SampleHold', 'Walk2', 'Walk']
    ]
  },
  {
    file: 'mixers1.png',
    crop: true,
    rows: [
      ['Mix8', 'Mix8x', 'Mix4', 'Mix4x']
    ]
  },
  {
    file: 'mixers2.png',
    crop: true,
    rows: [
      ['Mix1', 'Mix2', 'VCM', 'Mute8', 'Pan', 'XFade']
    ]
  },
  {
    file: 'mixers3.png',
    crop: true,
    rows: [
      ['UMix', 'Mumix', 'Matrix44', 'Matrix88']
    ]
  },
  {
    file: 'mixers4.png',
    crop: true,
    rows: [
      ['Switch44', 'Switch88', 'Switch1616']
    ]
  },
  {
    file: 'vcas.png',
    crop: true,
    rows: [
      ['VCA', 'VCAmp']
    ]
  },
  {
    file: 'dynamics.png',
    crop: true,
    rows: [
      ['AMRM', 'Pressor', 'Lmtr', 'Nsgt', 'CmpDist']
    ]
  },
  {
    file: 'sequencers1.png',
    crop: true,
    rows: [
      ['EightOne', 'OneEight', 'AddrSeq']
    ]
  },
  {
    file: 'sequencers2.png',
    crop: true,
    rows: [
      ['PGMR', 'PGMRX']
    ]
  },
  {
    file: 'visualizers.png',
    crop: true,
    rows: [
      ['Analyzer', 'AnalyzerXL', 'VU']
    ]
  },
  {
    file: 'poly1.png',
    crop: true,
    rows: [
      ['Mono', 'Arp', 'Assign', 'Unison']
    ]
  },
  {
    file: 'poly2.png',
    crop: true,
    rows: [
      ['PolyCon', 'Polycon8', 'PolyOff16', 'PolyOff8', 'PolyMult']
    ]
  },
  {
    file: 'pitch.png',
    crop: true,
    rows: [
      ['Detune', 'Stack', 'Reftone']
    ]
  },
  {
    file: 'utilities.png',
    crop: true,
    rows: [
      ['Bool', 'Cmp', 'CVD', 'FlipFlop', 'Inv', 'Manual', 'FourMan', 'Mult', 'Offset', 'Slew', 'Sums', 'Switch']
    ]
  },
  {
    file: 'misc.png',
    crop: true,
    rows: [
      ['Blank3', 'Blank6']
    ]
  }
]

HP = 15
PAD_EDGE = 1 * HP
PAD_MODULE = 1 * HP
PAD_GROUP = 3 * HP
OUT_DIR = './doc/www'
BACKGROUND_FILE = './doc/rack_background.png'

# require 'chunky_png'
require 'oily_png'
require 'pp'

screens_dir = ARGV[0]
if screens_dir.nil?
  STDERR.puts "Usage: #{$0}: <rack screenshot output directory for plugin>"
  exit 1
end

unless Dir.exists?(screens_dir)
  STDERR.puts "No such screenshots directory: #{screens_dir}"
  exit 1
end

$row_background = nil
def background_for_rows(n)
  unless $row_background
    background = ChunkyPNG::Image.from_file(BACKGROUND_FILE)
    $row_background = background.crop(0, 31, 15 * ((background.dimension.width - 10) / 15), 380)
  end

  out = ChunkyPNG::Image.new($row_background.dimension.width, n * $row_background.dimension.height, ChunkyPNG::Color::TRANSPARENT)
  (0...n).each do |i|
    out.compose!($row_background, 0, i * $row_background.dimension.height)
  end
  out
end

screens.each do |screen|
  next unless screen

  rows = screen[:rows]
  out = background_for_rows(rows.size)
  x = 0
  rows.each_with_index do |row, i|
    x = PAD_EDGE
    row.each_with_index do |item, j|
      if item == '-'
        x += PAD_GROUP
        x -= PAD_MODULE if j > 0
      else
        image = ChunkyPNG::Image.from_file(File.join(screens_dir, "Bogaudio-#{item}.png"))
        out.compose!(image, x, i * $row_background.dimension.height)
        x += image.dimension.width
        x += PAD_MODULE
      end
    end
    x -= PAD_MODULE if rows.last.size > 0
    x += PAD_EDGE
  end

  out.crop!(0, 0, x, out.dimension.height) if screen[:crop]

  file = File.join(OUT_DIR, screen[:file])
  out.save(file)
  puts "wrote #{file}"
  # system("open #{file}")
end
