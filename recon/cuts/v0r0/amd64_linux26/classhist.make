#-- start of make_header -----------------

#====================================
#  Application classhist
#
#   Generated Sun Feb  5 21:07:37 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_classhist_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_classhist_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_classhist

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classhist = /tmp/CMT_$(cuts_tag)_classhist.make$(cmt_lock_pid)
else
#cmt_local_tagfile_classhist = $(cuts_tag)_classhist.make
cmt_local_tagfile_classhist = $(bin)$(cuts_tag)_classhist.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_classhist = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_classhist = $(cuts_tag).make
cmt_local_tagfile_classhist = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_classhist)

ifdef cmt_classhist_has_target_tag

ifdef READONLY
cmt_final_setup_classhist = /tmp/CMT_cuts_classhistsetup.make
cmt_local_classhist_makefile = /tmp/CMT_classhist$(cmt_lock_pid).make
else
cmt_final_setup_classhist = $(bin)cuts_classhistsetup.make
cmt_local_classhist_makefile = $(bin)classhist.make
endif

else

ifdef READONLY
cmt_final_setup_classhist = /tmp/CMT_cutssetup.make
cmt_local_classhist_makefile = /tmp/CMT_classhist$(cmt_lock_pid).make
else
cmt_final_setup_classhist = $(bin)cutssetup.make
cmt_local_classhist_makefile = $(bin)classhist.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

classhist ::


ifdef READONLY
classhist ::
	@echo tags=$(tags)
	@echo cmt_local_tagfile=$(cmt_local_tagfile)
endif


dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'classhist'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = classhist/
classhist::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

classhist :: dirs  $(bin)classhist${application_suffix}
	$(echo) "classhist ok"

#-- end of application_header
#-- start of application

$(bin)classhist${application_suffix} :: $(bin)classhistcuts.o $(bin)classcuts.o $(use_stamps) $(classhiststamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)classhistcuts.o $(bin)classcuts.o $(cmt_installarea_linkopts) $(classhist_use_linkopts) $(classhistlinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
classhistinstallname = classhist${application_suffix}

classhist :: classhistinstall

install :: classhistinstall

classhistinstall :: $(install_dir)/$(classhistinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(classhistinstallname) :: $(bin)$(classhistinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classhistinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##classhistclean :: classhistuninstall

uninstall :: classhistuninstall

classhistuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(classhistinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (classhist.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),classhistclean)

#$(bin)classhist_dependencies.make :: dirs

ifndef QUICK
$(bin)classhist_dependencies.make : ../app/classhistcuts.C ../app/classcuts.C $(use_requirements) $(cmt_final_setup_classhist)
	$(echo) "(classhist.make) Rebuilding $@"; \
	  $(build_dependencies) classhist -all_sources -out=$@ ../app/classhistcuts.C ../app/classcuts.C
endif

#$(classhist_dependencies)

-include $(bin)classhist_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)classhist_dependencies.make : $(classhistcuts_C_dependencies)

$(bin)$(binobj)classhistcuts.o : $(classhistcuts_C_dependencies)
	$(cpp_echo) ../app/classhistcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classhist_pp_cppflags) $(app_classhist_pp_cppflags) $(classhistcuts_pp_cppflags) $(use_cppflags) $(classhist_cppflags) $(app_classhist_cppflags) $(classhistcuts_cppflags) $(classhistcuts_C_cppflags) -I../app ../app/classhistcuts.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)classhist_dependencies.make : $(classcuts_C_dependencies)

$(bin)$(binobj)classcuts.o : $(classcuts_C_dependencies)
	$(cpp_echo) ../app/classcuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(classhist_pp_cppflags) $(app_classhist_pp_cppflags) $(classcuts_pp_cppflags) $(use_cppflags) $(classhist_cppflags) $(app_classhist_cppflags) $(classcuts_cppflags) $(classcuts_C_cppflags) -I../app ../app/classcuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: classhistclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(classhist.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(classhist.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_classhist)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhist.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhist.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(classhist.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

classhistclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) classhist${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f classhist${application_suffix}

#	@echo "------> (classhist.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)classhistcuts.o $(bin)classcuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf classhist_deps classhist_dependencies.make
#-- end of cleanup_objects ------
