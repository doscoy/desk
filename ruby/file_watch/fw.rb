require 'rubygems'
require 'fssm'
require 'diff/lcs'

path = ARGV[0]

#load string from file
def loadfile(filename)
  file = nil
  open(filename, 'r') do |f|
    file = f.read
  end
  file
end


#laod inital file
old = loadfile(ARGV[0]).split('\n')

FSSM.monitor(File.dirname(path), File.basename(path)) do
  update do |basedir, filename|
    new = loadfile("#{basedir}/#{filename}").split("\n")
    diffs = Diff::LCS.sdiff(old, new)
    diffs.each do |d|
      if d.action == '+' or d.action == '!'
        puts "#{d.new_position}: > #{d.new_element}"
      end
      if d.action == '-' or d.action == '!'
        puts "#{d.old_position}: < #{d.old_element}"
      end
    end
    puts"----"
    old = new #update old
  end
end
