#JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
		$(JC) $*.java

CLASSES = \
		MySort.java 
		
default:	classes

classes: $(CLASSES:.java=.class)

clean:
		$(RM) *.class