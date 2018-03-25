## HybChive vision

### Vision:
Hybchive facilitates the use of a set of routines with the same functionality but with different implementations.

### Why is there a benefit of using routines with the same functionality but different implementations?
 - A user might want to exchange parts of code by different version with the same functionality. For example, a user might want to update a function that inverts a matrix by a faster or by a more accurate version.
 - A user might want to use all parts of heterogeneous hardware in parrallel which require different programming languages. For example, a user might want to use an Intel Xeon Phi, accessible by Intel TBB, and a NVIDIA GPGPU, accessible by CUDA, in parallel to speed up its job.

### What does HybChive do?
 - HybChive facilitates using an implementation with a certain attribute. For example, a user can easily decide if he wants to execute the fastest or the most accurate implementation in a HybChive - set
 - HybChive splits up the data if more than one implementation of a HybChive - set if used in parallel.

### What is a HybChive - set?
 - A HybChive set is a set of implementations with the same functionality. HybChive calls those implementations variants. A HybChive set could consist of one or more variants.

### What is a HybChive - variant?
 - A HybChive variant is part of of a HybChive set
 - A HybChive variant is a stand alone program created with the help of the HybChive template.
 - A HybChive - variant can itself consist of other HybChive variants of other HybChive - sets.

### How is a HybChive - set defined?
 - A HybChive set has a name and is defined by a purpose. For example, a HybChive - set with the name invertMatrix has the purpose to invert a matrix. Each variant in a HybChive - set has to pass a test, which consists in this case of the input and the output matrix. The test is executed by Travis-CI or locally by the user.

### How do I use HybChive?
 - Include HybChive as a library in your code
 - Access HybChive sets with the HybChive - function in your code
	 - to execute one variant with a certain attribute
	 - or to execute variants in parallel to access all parts of heterogeneous software

### With which computer languages can I use HybChive?
 - The HybChive scheduler is itself a stand alone program and reachable via an API.
 - It returns the result of the HybChive - function via linux ipc. Thus, libraries can be written in every language that can access Linux shared memory segments.
 - Since all variants are stand - alone programs, variants can be written as well in all languages that can access shared memory segments in Linux

### What do I need to use HybChive?
 - Linux
 - Docker

### How do I use HybChive?
 - Start HybChive:  
  
### To be implemented:
 - Semantic Versioning