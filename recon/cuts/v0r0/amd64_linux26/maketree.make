#-- start of make_header -----------------

#====================================
#  Application maketree
#
#   Generated Tue Feb  7 16:25:34 2012  by phuidn
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_maketree_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_maketree_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_maketree

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_maketree = /tmp/CMT_$(cuts_tag)_maketree.make$(cmt_lock_pid)
else
#cmt_local_tagfile_maketree = $(cuts_tag)_maketree.make
cmt_local_tagfile_maketree = $(bin)$(cuts_tag)_maketree.make
endif

else

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile_maketree = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile_maketree = $(cuts_tag).make
cmt_local_tagfile_maketree = $(bin)$(cuts_tag).make
endif

endif

-include $(cmt_local_tagfile_maketree)

ifdef cmt_maketree_has_target_tag

ifdef READONLY
cmt_final_setup_maketree = /tmp/CMT_cuts_maketreesetup.make
cmt_local_maketree_makefile = /tmp/CMT_maketree$(cmt_lock_pid).make
else
cmt_final_setup_maketree = $(bin)cuts_maketreesetup.make
cmt_local_maketree_makefile = $(bin)maketree.make
endif

else

ifdef READONLY
cmt_final_setup_maketree = /tmp/CMT_cutssetup.make
cmt_local_maketree_makefile = /tmp/CMT_maketree$(cmt_lock_pid).make
else
cmt_final_setup_maketree = $(bin)cutssetup.make
cmt_local_maketree_makefile = $(bin)maketree.make
endif

endif

ifdef READONLY
cmt_final_setup = /tmp/CMT_cutssetup.make
else
cmt_final_setup = $(bin)cutssetup.make
endif

maketree ::


ifdef READONLY
maketree ::
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
	$(echo) 'maketree'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = maketree/
maketree::
	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

#-- end of make_header ------------------

#-- start of application_header

maketree :: dirs  $(bin)maketree${application_suffix}
	$(echo) "maketree ok"

#-- end of application_header
#-- start of application

$(bin)maketree${application_suffix} :: $(bin)maketree.o $(bin)cuts.o $(use_stamps) $(maketreestamps) requirements $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)maketree.o $(bin)cuts.o $(cmt_installarea_linkopts) $(maketree_use_linkopts) $(maketreelinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
maketreeinstallname = maketree${application_suffix}

maketree :: maketreeinstall

install :: maketreeinstall

maketreeinstall :: $(install_dir)/$(maketreeinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(maketreeinstallname) :: $(bin)$(maketreeinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(maketreeinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##maketreeclean :: maketreeuninstall

uninstall :: maketreeuninstall

maketreeuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(maketreeinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (maketree.make) Removing installed files"
#-- end of application
#-- start of dependency ------------------
ifneq ($(MAKECMDGOALS),maketreeclean)

#$(bin)maketree_dependencies.make :: dirs

ifndef QUICK
$(bin)maketree_dependencies.make : ../app/maketree.C ../app/cuts.C $(use_requirements) $(cmt_final_setup_maketree)
	$(echo) "(maketree.make) Rebuilding $@"; \
	  $(build_dependencies) maketree -all_sources -out=$@ ../app/maketree.C ../app/cuts.C
endif

#$(maketree_dependencies)

-include $(bin)maketree_dependencies.make

endif
#-- end of dependency -------------------
#-- start of cpp ------

$(bin)maketree_dependencies.make : $(maketree_C_dependencies)

$(bin)$(binobj)maketree.o : $(maketree_C_dependencies)
	$(cpp_echo) ../app/maketree.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(maketree_pp_cppflags) $(app_maketree_pp_cppflags) $(maketree_pp_cppflags) $(use_cppflags) $(maketree_cppflags) $(app_maketree_cppflags) $(maketree_cppflags) $(maketree_C_cppflags) -I../app ../app/maketree.C

#-- end of cpp ------
#-- start of cpp ------

$(bin)maketree_dependencies.make : $(cuts_C_dependencies)

$(bin)$(binobj)cuts.o : $(cuts_C_dependencies)
	$(cpp_echo) ../app/cuts.C
	$(cpp_silent) $(cppcomp) -o $(@) $(use_pp_cppflags) $(maketree_pp_cppflags) $(app_maketree_pp_cppflags) $(cuts_pp_cppflags) $(use_cppflags) $(maketree_cppflags) $(app_maketree_cppflags) $(cuts_cppflags) $(cuts_C_cppflags) -I../app ../app/cuts.C

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: maketreeclean
	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(maketree.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: No rule for such target" >&2; exit
else
.DEFAULT::
	$(echo) "(maketree.make) PEDANTIC: $@: No rule for such target" >&2
	if test $@ = "$(cmt_final_setup)" -o\
	 $@ = "$(cmt_final_setup_maketree)" ; then\
	 found=n; for s in 1 2 3 4 5; do\
	 sleep $$s; test ! -f $@ || { found=y; break; }\
	 done; if test $$found = n; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(maketree.make) PEDANTIC: $@: Seems to be missing. Ignore it for now" >&2; exit 0 ; fi;\
	 elif test `expr index $@ '/'` -ne 0 ; then\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(maketree.make) PEDANTIC: $@: Seems to be a missing file. Please check" >&2; exit 2 ; \
	 else\
	 test -z "$(cmtmsg)" ||\
	 echo "$(CMTMSGPREFIX)" "(maketree.make) PEDANTIC: $@: Seems to be a fake target due to some pattern. Just ignore it" >&2 ; exit 0; fi
endif

maketreeclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) maketree${application_suffix}
	-$(cleanup_silent) cd $(bin); /bin/rm -f maketree${application_suffix}

#	@echo "------> (maketree.make) Removing application files"
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects
	-$(cleanup_silent) /bin/rm -f $(bin)maketree.o $(bin)cuts.o
	-$(cleanup_silent) cd $(bin); /bin/rm -rf maketree_deps maketree_dependencies.make
#-- end of cleanup_objects ------
