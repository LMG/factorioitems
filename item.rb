#!/usr/bin/ruby

class Item
  attr_accessor :components 

  def initialize(components = [])
    @components = components
  end
end
