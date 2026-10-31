DOCS     :=$(patsubst %.adoc,%.html,$(wildcard *.adoc))
DIAGRAMS :=$(patsubst %.dot,%.jpg,$(wildcard uml/*.dot))
UML_DIAGRAMS := $(patsubst uml/%.puml,images/%.png,$(wildcard uml/*.puml))


all: $(DIAGRAMS) $(UML_DIAGRAMS) $(DOCS)
diagrams: $(UML_DIAGRAMS) $(DIAGRAMS)

info:
	echo $(UML_DIAGRAMS)

%.html:%.adoc
	asciidoctor  $< 
#	asciidoctor -r asciidoctor-diagram  $< 

#	asciidoc -a theme=flask -o $@ $< 

%.jpg:%.dot
	dot -Tjpg -o $@  $<  
%.png:%.dot2Y
	dot -Tpng -o $@  $< 
	
#%.png : %.puml
#	plantuml $< 
#	
#%.png:%.pu
#	plantuml $<
#	
	
images/%.png : uml/%.puml
	plantuml $< 
	mv $(<:.puml=.png) $@
	
clean:
	rm -rf $(DOCS) $(DIAGRAMS)
