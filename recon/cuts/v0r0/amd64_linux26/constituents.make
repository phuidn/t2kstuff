
#-- start of constituents_header ------

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

tags      = $(tag),$(CMTEXTRATAGS)

cuts_tag = $(tag)

ifdef READONLY
cmt_local_tagfile = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile = $(cuts_tag).make
cmt_local_tagfile = $(bin)$(cuts_tag).make
endif

#-include $(cmt_local_tagfile)
include $(cmt_local_tagfile)

ifdef READONLY
cmt_local_setup = /tmp/CMT_cutssetup$(cmt_lock_pid).make
cmt_final_setup = /tmp/CMT_cutssetup.make
else
#cmt_local_setup = $(bin)cutssetup$(cmt_lock_pid).make
cmt_local_setup = $(bin)$(package)setup$$$$.make
#cmt_final_setup = $(bin)cutssetup.make
cmt_final_setup = $(bin)$(package)setup.make
endif

#--------------------------------------------------------

#cmt_lock_setup = /tmp/lock$(cmt_lock_pid).make
#cmt_temp_tag = /tmp/tag$(cmt_lock_pid).make

#first :: $(cmt_local_tagfile)
#	@echo $(cmt_local_tagfile) ok
ifndef QUICK
first :: $(cmt_final_setup) ;
else
first :: ;
endif

##	@bin=`$(cmtexe) show macro_value bin`

#$(cmt_local_tagfile) : $(cmt_lock_setup)
#	@echo "#CMT> Error: $@: No such file" >&2; exit 1
$(cmt_local_tagfile) :
	@echo "#CMT> Warning: $@: No such file" >&2; exit
#	@echo "#CMT> Info: $@: No need to rebuild file" >&2; exit

$(cmt_final_setup) : $(cmt_local_tagfile) 
	$(echo) "(constituents.make) Rebuilding $@"
	@if test ! -d $(@D); then $(mkdir) -p $(@D); fi; \
	  if test -f $(cmt_local_setup); then /bin/rm -f $(cmt_local_setup); fi; \
	  trap '/bin/rm -f $(cmt_local_setup)' 0 1 2 15; \
	  $(cmtexe) -tag=$(tags) show setup >>$(cmt_local_setup); \
	  if test ! -f $@; then \
	    mv $(cmt_local_setup) $@; \
	  else \
	    if /usr/bin/diff $(cmt_local_setup) $@ >/dev/null ; then \
	      : ; \
	    else \
	      mv $(cmt_local_setup) $@; \
	    fi; \
	  fi

#	@/bin/echo $@ ok   

config :: checkuses
	@exit 0
checkuses : ;

env.make ::
	printenv >env.make.tmp; $(cmtexe) check files env.make.tmp env.make

ifndef QUICK
all :: build_library_links
	$(echo) "(constituents.make) all done"
endif

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

build_library_links : dirs requirements
	$(echo) "(constituents.make) Rebuilding library links"; \
	if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi; \
	$(build_library_links)

.DEFAULT ::
	$(echo) "(constituents.make) $@: No rule for such target" >&2
#	@echo "#CMT> Warning: $@: Using default commands" >&2; exit

#	@if test "$@" = "$(cmt_lock_setup)"; then \
	#  /bin/rm -f $(cmt_lock_setup); \
	 # touch $(cmt_lock_setup); \
	#fi

#-- end of constituents_header ------
#-- start of group ------

all_groups :: all

all :: $(all_dependencies)  $(all_pre_constituents) $(all_constituents)  $(all_post_constituents)
	$(echo) "all ok."

#	@/bin/echo " all ok."

clean :: allclean

allclean ::  $(all_constituentsclean)
	$(echo) $(all_constituentsclean)
	$(echo) "allclean ok."

#	@echo $(all_constituentsclean)
#	@/bin/echo " allclean ok."

allclean :: makefilesclean

#-- end of group ------
#-- start of group ------

all_groups :: cmt_actions

cmt_actions :: $(cmt_actions_dependencies)  $(cmt_actions_pre_constituents) $(cmt_actions_constituents)  $(cmt_actions_post_constituents)
	$(echo) "cmt_actions ok."

#	@/bin/echo " cmt_actions ok."

clean :: allclean

cmt_actionsclean ::  $(cmt_actions_constituentsclean)
	$(echo) $(cmt_actions_constituentsclean)
	$(echo) "cmt_actionsclean ok."

#	@echo $(cmt_actions_constituentsclean)
#	@/bin/echo " cmt_actionsclean ok."

cmt_actionsclean :: makefilesclean

#-- end of group ------
#-- start of constituent ------

cmt_applycuts_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_applycuts_has_target_tag

ifdef READONLY
cmt_local_tagfile_applycuts = /tmp/CMT_$(cuts_tag)_applycuts.make$(cmt_lock_pid)
cmt_final_setup_applycuts = /tmp/CMT_cuts_applycutssetup.make
cmt_local_applycuts_makefile = /tmp/CMT_applycuts$(cmt_lock_pid).make
else
#cmt_local_tagfile_applycuts = $(cuts_tag)_applycuts.make
cmt_local_tagfile_applycuts = $(bin)$(cuts_tag)_applycuts.make
cmt_final_setup_applycuts = $(bin)cuts_applycutssetup.make
cmt_local_applycuts_makefile = $(bin)applycuts.make
endif

applycuts_extratags = -tag_add=target_applycuts

#$(cmt_local_tagfile_applycuts) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_applycuts) ::
else
$(cmt_local_tagfile_applycuts) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_applycuts)"
	@if test -f $(cmt_local_tagfile_applycuts); then /bin/rm -f $(cmt_local_tagfile_applycuts); fi ; \
	  $(cmtexe) -tag=$(tags) $(applycuts_extratags) build tag_makefile >>$(cmt_local_tagfile_applycuts); \
	  if test -f $(cmt_final_setup_applycuts); then /bin/rm -f $(cmt_final_setup_applycuts); fi; \
	  $(cmtexe) -tag=$(tags) $(applycuts_extratags) show setup >>$(cmt_final_setup_applycuts)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_applycuts = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
cmt_final_setup_applycuts = /tmp/CMT_cutssetup.make
cmt_local_applycuts_makefile = /tmp/CMT_applycuts$(cmt_lock_pid).make
else
#cmt_local_tagfile_applycuts = $(cuts_tag).make
cmt_local_tagfile_applycuts = $(bin)$(cuts_tag).make
cmt_final_setup_applycuts = $(bin)cutssetup.make
cmt_local_applycuts_makefile = $(bin)applycuts.make
endif

endif

ifndef QUICK
$(cmt_local_applycuts_makefile) :: $(applycuts_dependencies) $(cmt_local_tagfile_applycuts) build_library_links dirs
else
$(cmt_local_applycuts_makefile) :: $(cmt_local_tagfile_applycuts)
endif
	$(echo) "(constituents.make) Building applycuts.make"; \
	  $(cmtexe) -tag=$(tags) $(applycuts_extratags) build constituent_makefile -out=$(cmt_local_applycuts_makefile) applycuts

applycuts :: $(applycuts_dependencies) $(cmt_local_applycuts_makefile)
	$(echo) "(constituents.make) Starting applycuts"
	@$(MAKE) -f $(cmt_local_applycuts_makefile) cmt_lock_pid=$${cmt_lock_pid} applycuts
	$(echo) "(constituents.make) applycuts done"

clean :: applycutsclean

applycutsclean :: $(applycutsclean_dependencies) ##$(cmt_local_applycuts_makefile)
	$(echo) "(constituents.make) Starting applycutsclean"
	@-if test -f $(cmt_local_applycuts_makefile); then \
	  $(MAKE) -f $(cmt_local_applycuts_makefile) cmt_lock_pid=$${cmt_lock_pid} applycutsclean; \
	fi

##	  /bin/rm -f $(cmt_local_applycuts_makefile) $(bin)applycuts_dependencies.make

install :: applycutsinstall

applycutsinstall :: $(applycuts_dependencies) $(cmt_local_applycuts_makefile)
	$(echo) "(constituents.make) Starting install applycuts"
	@-$(MAKE) -f $(cmt_local_applycuts_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install applycuts done"

uninstall :: applycutsuninstall

applycutsuninstall :: $(cmt_local_applycuts_makefile)
	$(echo) "(constituents.make) Starting uninstall applycuts"
	@-$(MAKE) -f $(cmt_local_applycuts_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall applycuts done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ applycuts"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ applycuts done"
endif


#-- end of constituent ------
#-- start of constituent ------

cmt_hist_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_hist_has_target_tag

ifdef READONLY
cmt_local_tagfile_hist = /tmp/CMT_$(cuts_tag)_hist.make$(cmt_lock_pid)
cmt_final_setup_hist = /tmp/CMT_cuts_histsetup.make
cmt_local_hist_makefile = /tmp/CMT_hist$(cmt_lock_pid).make
else
#cmt_local_tagfile_hist = $(cuts_tag)_hist.make
cmt_local_tagfile_hist = $(bin)$(cuts_tag)_hist.make
cmt_final_setup_hist = $(bin)cuts_histsetup.make
cmt_local_hist_makefile = $(bin)hist.make
endif

hist_extratags = -tag_add=target_hist

#$(cmt_local_tagfile_hist) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_hist) ::
else
$(cmt_local_tagfile_hist) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_hist)"
	@if test -f $(cmt_local_tagfile_hist); then /bin/rm -f $(cmt_local_tagfile_hist); fi ; \
	  $(cmtexe) -tag=$(tags) $(hist_extratags) build tag_makefile >>$(cmt_local_tagfile_hist); \
	  if test -f $(cmt_final_setup_hist); then /bin/rm -f $(cmt_final_setup_hist); fi; \
	  $(cmtexe) -tag=$(tags) $(hist_extratags) show setup >>$(cmt_final_setup_hist)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_hist = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
cmt_final_setup_hist = /tmp/CMT_cutssetup.make
cmt_local_hist_makefile = /tmp/CMT_hist$(cmt_lock_pid).make
else
#cmt_local_tagfile_hist = $(cuts_tag).make
cmt_local_tagfile_hist = $(bin)$(cuts_tag).make
cmt_final_setup_hist = $(bin)cutssetup.make
cmt_local_hist_makefile = $(bin)hist.make
endif

endif

ifndef QUICK
$(cmt_local_hist_makefile) :: $(hist_dependencies) $(cmt_local_tagfile_hist) build_library_links dirs
else
$(cmt_local_hist_makefile) :: $(cmt_local_tagfile_hist)
endif
	$(echo) "(constituents.make) Building hist.make"; \
	  $(cmtexe) -tag=$(tags) $(hist_extratags) build constituent_makefile -out=$(cmt_local_hist_makefile) hist

hist :: $(hist_dependencies) $(cmt_local_hist_makefile)
	$(echo) "(constituents.make) Starting hist"
	@$(MAKE) -f $(cmt_local_hist_makefile) cmt_lock_pid=$${cmt_lock_pid} hist
	$(echo) "(constituents.make) hist done"

clean :: histclean

histclean :: $(histclean_dependencies) ##$(cmt_local_hist_makefile)
	$(echo) "(constituents.make) Starting histclean"
	@-if test -f $(cmt_local_hist_makefile); then \
	  $(MAKE) -f $(cmt_local_hist_makefile) cmt_lock_pid=$${cmt_lock_pid} histclean; \
	fi

##	  /bin/rm -f $(cmt_local_hist_makefile) $(bin)hist_dependencies.make

install :: histinstall

histinstall :: $(hist_dependencies) $(cmt_local_hist_makefile)
	$(echo) "(constituents.make) Starting install hist"
	@-$(MAKE) -f $(cmt_local_hist_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install hist done"

uninstall :: histuninstall

histuninstall :: $(cmt_local_hist_makefile)
	$(echo) "(constituents.make) Starting uninstall hist"
	@-$(MAKE) -f $(cmt_local_hist_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall hist done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ hist"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ hist done"
endif


#-- end of constituent ------
#-- start of constituent ------

cmt_maketree_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_maketree_has_target_tag

ifdef READONLY
cmt_local_tagfile_maketree = /tmp/CMT_$(cuts_tag)_maketree.make$(cmt_lock_pid)
cmt_final_setup_maketree = /tmp/CMT_cuts_maketreesetup.make
cmt_local_maketree_makefile = /tmp/CMT_maketree$(cmt_lock_pid).make
else
#cmt_local_tagfile_maketree = $(cuts_tag)_maketree.make
cmt_local_tagfile_maketree = $(bin)$(cuts_tag)_maketree.make
cmt_final_setup_maketree = $(bin)cuts_maketreesetup.make
cmt_local_maketree_makefile = $(bin)maketree.make
endif

maketree_extratags = -tag_add=target_maketree

#$(cmt_local_tagfile_maketree) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_maketree) ::
else
$(cmt_local_tagfile_maketree) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_maketree)"
	@if test -f $(cmt_local_tagfile_maketree); then /bin/rm -f $(cmt_local_tagfile_maketree); fi ; \
	  $(cmtexe) -tag=$(tags) $(maketree_extratags) build tag_makefile >>$(cmt_local_tagfile_maketree); \
	  if test -f $(cmt_final_setup_maketree); then /bin/rm -f $(cmt_final_setup_maketree); fi; \
	  $(cmtexe) -tag=$(tags) $(maketree_extratags) show setup >>$(cmt_final_setup_maketree)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_maketree = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
cmt_final_setup_maketree = /tmp/CMT_cutssetup.make
cmt_local_maketree_makefile = /tmp/CMT_maketree$(cmt_lock_pid).make
else
#cmt_local_tagfile_maketree = $(cuts_tag).make
cmt_local_tagfile_maketree = $(bin)$(cuts_tag).make
cmt_final_setup_maketree = $(bin)cutssetup.make
cmt_local_maketree_makefile = $(bin)maketree.make
endif

endif

ifndef QUICK
$(cmt_local_maketree_makefile) :: $(maketree_dependencies) $(cmt_local_tagfile_maketree) build_library_links dirs
else
$(cmt_local_maketree_makefile) :: $(cmt_local_tagfile_maketree)
endif
	$(echo) "(constituents.make) Building maketree.make"; \
	  $(cmtexe) -tag=$(tags) $(maketree_extratags) build constituent_makefile -out=$(cmt_local_maketree_makefile) maketree

maketree :: $(maketree_dependencies) $(cmt_local_maketree_makefile)
	$(echo) "(constituents.make) Starting maketree"
	@$(MAKE) -f $(cmt_local_maketree_makefile) cmt_lock_pid=$${cmt_lock_pid} maketree
	$(echo) "(constituents.make) maketree done"

clean :: maketreeclean

maketreeclean :: $(maketreeclean_dependencies) ##$(cmt_local_maketree_makefile)
	$(echo) "(constituents.make) Starting maketreeclean"
	@-if test -f $(cmt_local_maketree_makefile); then \
	  $(MAKE) -f $(cmt_local_maketree_makefile) cmt_lock_pid=$${cmt_lock_pid} maketreeclean; \
	fi

##	  /bin/rm -f $(cmt_local_maketree_makefile) $(bin)maketree_dependencies.make

install :: maketreeinstall

maketreeinstall :: $(maketree_dependencies) $(cmt_local_maketree_makefile)
	$(echo) "(constituents.make) Starting install maketree"
	@-$(MAKE) -f $(cmt_local_maketree_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install maketree done"

uninstall :: maketreeuninstall

maketreeuninstall :: $(cmt_local_maketree_makefile)
	$(echo) "(constituents.make) Starting uninstall maketree"
	@-$(MAKE) -f $(cmt_local_maketree_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall maketree done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ maketree"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ maketree done"
endif


#-- end of constituent ------
#-- start of constituent_lock ------

cmt_make_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_make_has_target_tag

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(cuts_tag)_make.make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_cuts_makesetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(cuts_tag)_make.make
cmt_local_tagfile_make = $(bin)$(cuts_tag)_make.make
cmt_final_setup_make = $(bin)cuts_makesetup.make
cmt_local_make_makefile = $(bin)make.make
endif

make_extratags = -tag_add=target_make

#$(cmt_local_tagfile_make) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_make) ::
else
$(cmt_local_tagfile_make) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_make)"
	@if test -f $(cmt_local_tagfile_make); then /bin/rm -f $(cmt_local_tagfile_make); fi ; \
	  $(cmtexe) -tag=$(tags) $(make_extratags) build tag_makefile >>$(cmt_local_tagfile_make); \
	  if test -f $(cmt_final_setup_make); then /bin/rm -f $(cmt_final_setup_make); fi; \
	  $(cmtexe) -tag=$(tags) $(make_extratags) show setup >>$(cmt_final_setup_make)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_cutssetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(cuts_tag).make
cmt_local_tagfile_make = $(bin)$(cuts_tag).make
cmt_final_setup_make = $(bin)cutssetup.make
cmt_local_make_makefile = $(bin)make.make
endif

endif

ifndef QUICK
$(cmt_local_make_makefile) :: $(make_dependencies) $(cmt_local_tagfile_make) build_library_links dirs
else
$(cmt_local_make_makefile) :: $(cmt_local_tagfile_make)
endif
	$(echo) "(constituents.make) Building make.make"; \
	  $(cmtexe) -tag=$(tags) $(make_extratags) build constituent_makefile -out=$(cmt_local_make_makefile) make

make :: $(make_dependencies) $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Creating make${lock_suffix} and Starting make"
	@${lock_command} make${lock_suffix} || exit $$?; \
	  retval=$$?; \
	  trap '${unlock_command} make${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} make; \
	  retval=$$?; ${unlock_command} make${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) make done"

clean :: makeclean

makeclean :: $(makeclean_dependencies) ##$(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting makeclean"
	@-if test -f $(cmt_local_make_makefile); then \
	  $(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} makeclean; \
	fi

##	  /bin/rm -f $(cmt_local_make_makefile) $(bin)make_dependencies.make

install :: makeinstall

makeinstall :: $(make_dependencies) $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting install make"
	@-$(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install make done"

uninstall :: makeuninstall

makeuninstall :: $(cmt_local_make_makefile)
	$(echo) "(constituents.make) Starting uninstall make"
	@-$(MAKE) -f $(cmt_local_make_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall make done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ make"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ make done"
endif


#-- end of constituent_lock ------
#-- start of constituent_lock ------

cmt_warnCALIBRECON_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_warnCALIBRECON_has_target_tag

ifdef READONLY
cmt_local_tagfile_warnCALIBRECON = /tmp/CMT_$(cuts_tag)_warnCALIBRECON.make$(cmt_lock_pid)
cmt_final_setup_warnCALIBRECON = /tmp/CMT_cuts_warnCALIBRECONsetup.make
cmt_local_warnCALIBRECON_makefile = /tmp/CMT_warnCALIBRECON$(cmt_lock_pid).make
else
#cmt_local_tagfile_warnCALIBRECON = $(cuts_tag)_warnCALIBRECON.make
cmt_local_tagfile_warnCALIBRECON = $(bin)$(cuts_tag)_warnCALIBRECON.make
cmt_final_setup_warnCALIBRECON = $(bin)cuts_warnCALIBRECONsetup.make
cmt_local_warnCALIBRECON_makefile = $(bin)warnCALIBRECON.make
endif

warnCALIBRECON_extratags = -tag_add=target_warnCALIBRECON

#$(cmt_local_tagfile_warnCALIBRECON) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_warnCALIBRECON) ::
else
$(cmt_local_tagfile_warnCALIBRECON) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_warnCALIBRECON)"
	@if test -f $(cmt_local_tagfile_warnCALIBRECON); then /bin/rm -f $(cmt_local_tagfile_warnCALIBRECON); fi ; \
	  $(cmtexe) -tag=$(tags) $(warnCALIBRECON_extratags) build tag_makefile >>$(cmt_local_tagfile_warnCALIBRECON); \
	  if test -f $(cmt_final_setup_warnCALIBRECON); then /bin/rm -f $(cmt_final_setup_warnCALIBRECON); fi; \
	  $(cmtexe) -tag=$(tags) $(warnCALIBRECON_extratags) show setup >>$(cmt_final_setup_warnCALIBRECON)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_warnCALIBRECON = /tmp/CMT_$(cuts_tag).make$(cmt_lock_pid)
cmt_final_setup_warnCALIBRECON = /tmp/CMT_cutssetup.make
cmt_local_warnCALIBRECON_makefile = /tmp/CMT_warnCALIBRECON$(cmt_lock_pid).make
else
#cmt_local_tagfile_warnCALIBRECON = $(cuts_tag).make
cmt_local_tagfile_warnCALIBRECON = $(bin)$(cuts_tag).make
cmt_final_setup_warnCALIBRECON = $(bin)cutssetup.make
cmt_local_warnCALIBRECON_makefile = $(bin)warnCALIBRECON.make
endif

endif

ifndef QUICK
$(cmt_local_warnCALIBRECON_makefile) :: $(warnCALIBRECON_dependencies) $(cmt_local_tagfile_warnCALIBRECON) build_library_links dirs
else
$(cmt_local_warnCALIBRECON_makefile) :: $(cmt_local_tagfile_warnCALIBRECON)
endif
	$(echo) "(constituents.make) Building warnCALIBRECON.make"; \
	  $(cmtexe) -tag=$(tags) $(warnCALIBRECON_extratags) build constituent_makefile -out=$(cmt_local_warnCALIBRECON_makefile) warnCALIBRECON

warnCALIBRECON :: $(warnCALIBRECON_dependencies) $(cmt_local_warnCALIBRECON_makefile)
	$(echo) "(constituents.make) Creating warnCALIBRECON${lock_suffix} and Starting warnCALIBRECON"
	@${lock_command} warnCALIBRECON${lock_suffix} || exit $$?; \
	  retval=$$?; \
	  trap '${unlock_command} warnCALIBRECON${lock_suffix}; exit $${retval}' 1 2 15; \
	  $(MAKE) -f $(cmt_local_warnCALIBRECON_makefile) cmt_lock_pid=$${cmt_lock_pid} warnCALIBRECON; \
	  retval=$$?; ${unlock_command} warnCALIBRECON${lock_suffix}; exit $${retval}
	$(echo) "(constituents.make) warnCALIBRECON done"

clean :: warnCALIBRECONclean

warnCALIBRECONclean :: $(warnCALIBRECONclean_dependencies) ##$(cmt_local_warnCALIBRECON_makefile)
	$(echo) "(constituents.make) Starting warnCALIBRECONclean"
	@-if test -f $(cmt_local_warnCALIBRECON_makefile); then \
	  $(MAKE) -f $(cmt_local_warnCALIBRECON_makefile) cmt_lock_pid=$${cmt_lock_pid} warnCALIBRECONclean; \
	fi

##	  /bin/rm -f $(cmt_local_warnCALIBRECON_makefile) $(bin)warnCALIBRECON_dependencies.make

install :: warnCALIBRECONinstall

warnCALIBRECONinstall :: $(warnCALIBRECON_dependencies) $(cmt_local_warnCALIBRECON_makefile)
	$(echo) "(constituents.make) Starting install warnCALIBRECON"
	@-$(MAKE) -f $(cmt_local_warnCALIBRECON_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install warnCALIBRECON done"

uninstall :: warnCALIBRECONuninstall

warnCALIBRECONuninstall :: $(cmt_local_warnCALIBRECON_makefile)
	$(echo) "(constituents.make) Starting uninstall warnCALIBRECON"
	@-$(MAKE) -f $(cmt_local_warnCALIBRECON_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall warnCALIBRECON done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ warnCALIBRECON"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ warnCALIBRECON done"
endif


#-- end of constituent_lock ------
#-- start of constituents_trailer ------

clean :: remove_library_links

remove_library_links ::
	$(echo) "Removing library links"; \
	  $(remove_library_links)

makefilesclean ::

###	@/bin/rm -f checkuses

###	/bin/rm -f *.make*

clean :: makefilesclean

binclean :: clean
	$(echo) "Removing binary directory $(bin)"
	@if test ! "$(bin)" = "./"; then \
	  /bin/rm -rf $(bin); \
	fi

#-- end of constituents_trailer ------
