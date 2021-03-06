
#-- start of constituents_header ------

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

tags      = $(tag),$(CMTEXTRATAGS)

evestrip_tag = $(tag)

ifdef READONLY
cmt_local_tagfile = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
else
#cmt_local_tagfile = $(evestrip_tag).make
cmt_local_tagfile = $(bin)$(evestrip_tag).make
endif

#-include $(cmt_local_tagfile)
include $(cmt_local_tagfile)

ifdef READONLY
cmt_local_setup = /tmp/CMT_evestripsetup$(cmt_lock_pid).make
cmt_final_setup = /tmp/CMT_evestripsetup.make
else
#cmt_local_setup = $(bin)evestripsetup$(cmt_lock_pid).make
cmt_local_setup = $(bin)$(package)setup$$$$.make
#cmt_final_setup = $(bin)evestripsetup.make
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

cmt_EventFilter_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_EventFilter_has_target_tag

ifdef READONLY
cmt_local_tagfile_EventFilter = /tmp/CMT_$(evestrip_tag)_EventFilter.make$(cmt_lock_pid)
cmt_final_setup_EventFilter = /tmp/CMT_evestrip_EventFiltersetup.make
cmt_local_EventFilter_makefile = /tmp/CMT_EventFilter$(cmt_lock_pid).make
else
#cmt_local_tagfile_EventFilter = $(evestrip_tag)_EventFilter.make
cmt_local_tagfile_EventFilter = $(bin)$(evestrip_tag)_EventFilter.make
cmt_final_setup_EventFilter = $(bin)evestrip_EventFiltersetup.make
cmt_local_EventFilter_makefile = $(bin)EventFilter.make
endif

EventFilter_extratags = -tag_add=target_EventFilter

#$(cmt_local_tagfile_EventFilter) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_EventFilter) ::
else
$(cmt_local_tagfile_EventFilter) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_EventFilter)"
	@if test -f $(cmt_local_tagfile_EventFilter); then /bin/rm -f $(cmt_local_tagfile_EventFilter); fi ; \
	  $(cmtexe) -tag=$(tags) $(EventFilter_extratags) build tag_makefile >>$(cmt_local_tagfile_EventFilter); \
	  if test -f $(cmt_final_setup_EventFilter); then /bin/rm -f $(cmt_final_setup_EventFilter); fi; \
	  $(cmtexe) -tag=$(tags) $(EventFilter_extratags) show setup >>$(cmt_final_setup_EventFilter)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_EventFilter = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
cmt_final_setup_EventFilter = /tmp/CMT_evestripsetup.make
cmt_local_EventFilter_makefile = /tmp/CMT_EventFilter$(cmt_lock_pid).make
else
#cmt_local_tagfile_EventFilter = $(evestrip_tag).make
cmt_local_tagfile_EventFilter = $(bin)$(evestrip_tag).make
cmt_final_setup_EventFilter = $(bin)evestripsetup.make
cmt_local_EventFilter_makefile = $(bin)EventFilter.make
endif

endif

ifndef QUICK
$(cmt_local_EventFilter_makefile) :: $(EventFilter_dependencies) $(cmt_local_tagfile_EventFilter) build_library_links dirs
else
$(cmt_local_EventFilter_makefile) :: $(cmt_local_tagfile_EventFilter)
endif
	$(echo) "(constituents.make) Building EventFilter.make"; \
	  $(cmtexe) -tag=$(tags) $(EventFilter_extratags) build constituent_makefile -out=$(cmt_local_EventFilter_makefile) EventFilter

EventFilter :: $(EventFilter_dependencies) $(cmt_local_EventFilter_makefile)
	$(echo) "(constituents.make) Starting EventFilter"
	@$(MAKE) -f $(cmt_local_EventFilter_makefile) cmt_lock_pid=$${cmt_lock_pid} EventFilter
	$(echo) "(constituents.make) EventFilter done"

clean :: EventFilterclean

EventFilterclean :: $(EventFilterclean_dependencies) ##$(cmt_local_EventFilter_makefile)
	$(echo) "(constituents.make) Starting EventFilterclean"
	@-if test -f $(cmt_local_EventFilter_makefile); then \
	  $(MAKE) -f $(cmt_local_EventFilter_makefile) cmt_lock_pid=$${cmt_lock_pid} EventFilterclean; \
	fi

##	  /bin/rm -f $(cmt_local_EventFilter_makefile) $(bin)EventFilter_dependencies.make

install :: EventFilterinstall

EventFilterinstall :: $(EventFilter_dependencies) $(cmt_local_EventFilter_makefile)
	$(echo) "(constituents.make) Starting install EventFilter"
	@-$(MAKE) -f $(cmt_local_EventFilter_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install EventFilter done"

uninstall :: EventFilteruninstall

EventFilteruninstall :: $(cmt_local_EventFilter_makefile)
	$(echo) "(constituents.make) Starting uninstall EventFilter"
	@-$(MAKE) -f $(cmt_local_EventFilter_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall EventFilter done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ EventFilter"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ EventFilter done"
endif


#-- end of constituent ------
#-- start of constituent ------

cmt_PrintEvent_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_PrintEvent_has_target_tag

ifdef READONLY
cmt_local_tagfile_PrintEvent = /tmp/CMT_$(evestrip_tag)_PrintEvent.make$(cmt_lock_pid)
cmt_final_setup_PrintEvent = /tmp/CMT_evestrip_PrintEventsetup.make
cmt_local_PrintEvent_makefile = /tmp/CMT_PrintEvent$(cmt_lock_pid).make
else
#cmt_local_tagfile_PrintEvent = $(evestrip_tag)_PrintEvent.make
cmt_local_tagfile_PrintEvent = $(bin)$(evestrip_tag)_PrintEvent.make
cmt_final_setup_PrintEvent = $(bin)evestrip_PrintEventsetup.make
cmt_local_PrintEvent_makefile = $(bin)PrintEvent.make
endif

PrintEvent_extratags = -tag_add=target_PrintEvent

#$(cmt_local_tagfile_PrintEvent) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_PrintEvent) ::
else
$(cmt_local_tagfile_PrintEvent) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_PrintEvent)"
	@if test -f $(cmt_local_tagfile_PrintEvent); then /bin/rm -f $(cmt_local_tagfile_PrintEvent); fi ; \
	  $(cmtexe) -tag=$(tags) $(PrintEvent_extratags) build tag_makefile >>$(cmt_local_tagfile_PrintEvent); \
	  if test -f $(cmt_final_setup_PrintEvent); then /bin/rm -f $(cmt_final_setup_PrintEvent); fi; \
	  $(cmtexe) -tag=$(tags) $(PrintEvent_extratags) show setup >>$(cmt_final_setup_PrintEvent)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_PrintEvent = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
cmt_final_setup_PrintEvent = /tmp/CMT_evestripsetup.make
cmt_local_PrintEvent_makefile = /tmp/CMT_PrintEvent$(cmt_lock_pid).make
else
#cmt_local_tagfile_PrintEvent = $(evestrip_tag).make
cmt_local_tagfile_PrintEvent = $(bin)$(evestrip_tag).make
cmt_final_setup_PrintEvent = $(bin)evestripsetup.make
cmt_local_PrintEvent_makefile = $(bin)PrintEvent.make
endif

endif

ifndef QUICK
$(cmt_local_PrintEvent_makefile) :: $(PrintEvent_dependencies) $(cmt_local_tagfile_PrintEvent) build_library_links dirs
else
$(cmt_local_PrintEvent_makefile) :: $(cmt_local_tagfile_PrintEvent)
endif
	$(echo) "(constituents.make) Building PrintEvent.make"; \
	  $(cmtexe) -tag=$(tags) $(PrintEvent_extratags) build constituent_makefile -out=$(cmt_local_PrintEvent_makefile) PrintEvent

PrintEvent :: $(PrintEvent_dependencies) $(cmt_local_PrintEvent_makefile)
	$(echo) "(constituents.make) Starting PrintEvent"
	@$(MAKE) -f $(cmt_local_PrintEvent_makefile) cmt_lock_pid=$${cmt_lock_pid} PrintEvent
	$(echo) "(constituents.make) PrintEvent done"

clean :: PrintEventclean

PrintEventclean :: $(PrintEventclean_dependencies) ##$(cmt_local_PrintEvent_makefile)
	$(echo) "(constituents.make) Starting PrintEventclean"
	@-if test -f $(cmt_local_PrintEvent_makefile); then \
	  $(MAKE) -f $(cmt_local_PrintEvent_makefile) cmt_lock_pid=$${cmt_lock_pid} PrintEventclean; \
	fi

##	  /bin/rm -f $(cmt_local_PrintEvent_makefile) $(bin)PrintEvent_dependencies.make

install :: PrintEventinstall

PrintEventinstall :: $(PrintEvent_dependencies) $(cmt_local_PrintEvent_makefile)
	$(echo) "(constituents.make) Starting install PrintEvent"
	@-$(MAKE) -f $(cmt_local_PrintEvent_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install PrintEvent done"

uninstall :: PrintEventuninstall

PrintEventuninstall :: $(cmt_local_PrintEvent_makefile)
	$(echo) "(constituents.make) Starting uninstall PrintEvent"
	@-$(MAKE) -f $(cmt_local_PrintEvent_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall PrintEvent done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ PrintEvent"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ PrintEvent done"
endif


#-- end of constituent ------
#-- start of constituent ------

cmt_FirstPass_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_FirstPass_has_target_tag

ifdef READONLY
cmt_local_tagfile_FirstPass = /tmp/CMT_$(evestrip_tag)_FirstPass.make$(cmt_lock_pid)
cmt_final_setup_FirstPass = /tmp/CMT_evestrip_FirstPasssetup.make
cmt_local_FirstPass_makefile = /tmp/CMT_FirstPass$(cmt_lock_pid).make
else
#cmt_local_tagfile_FirstPass = $(evestrip_tag)_FirstPass.make
cmt_local_tagfile_FirstPass = $(bin)$(evestrip_tag)_FirstPass.make
cmt_final_setup_FirstPass = $(bin)evestrip_FirstPasssetup.make
cmt_local_FirstPass_makefile = $(bin)FirstPass.make
endif

FirstPass_extratags = -tag_add=target_FirstPass

#$(cmt_local_tagfile_FirstPass) : $(cmt_lock_setup)
ifndef QUICK
$(cmt_local_tagfile_FirstPass) ::
else
$(cmt_local_tagfile_FirstPass) :
endif
	$(echo) "(constituents.make) Rebuilding setup.make $(cmt_local_tagfile_FirstPass)"
	@if test -f $(cmt_local_tagfile_FirstPass); then /bin/rm -f $(cmt_local_tagfile_FirstPass); fi ; \
	  $(cmtexe) -tag=$(tags) $(FirstPass_extratags) build tag_makefile >>$(cmt_local_tagfile_FirstPass); \
	  if test -f $(cmt_final_setup_FirstPass); then /bin/rm -f $(cmt_final_setup_FirstPass); fi; \
	  $(cmtexe) -tag=$(tags) $(FirstPass_extratags) show setup >>$(cmt_final_setup_FirstPass)
	$(echo) setup.make ok

else

ifdef READONLY
cmt_local_tagfile_FirstPass = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
cmt_final_setup_FirstPass = /tmp/CMT_evestripsetup.make
cmt_local_FirstPass_makefile = /tmp/CMT_FirstPass$(cmt_lock_pid).make
else
#cmt_local_tagfile_FirstPass = $(evestrip_tag).make
cmt_local_tagfile_FirstPass = $(bin)$(evestrip_tag).make
cmt_final_setup_FirstPass = $(bin)evestripsetup.make
cmt_local_FirstPass_makefile = $(bin)FirstPass.make
endif

endif

ifndef QUICK
$(cmt_local_FirstPass_makefile) :: $(FirstPass_dependencies) $(cmt_local_tagfile_FirstPass) build_library_links dirs
else
$(cmt_local_FirstPass_makefile) :: $(cmt_local_tagfile_FirstPass)
endif
	$(echo) "(constituents.make) Building FirstPass.make"; \
	  $(cmtexe) -tag=$(tags) $(FirstPass_extratags) build constituent_makefile -out=$(cmt_local_FirstPass_makefile) FirstPass

FirstPass :: $(FirstPass_dependencies) $(cmt_local_FirstPass_makefile)
	$(echo) "(constituents.make) Starting FirstPass"
	@$(MAKE) -f $(cmt_local_FirstPass_makefile) cmt_lock_pid=$${cmt_lock_pid} FirstPass
	$(echo) "(constituents.make) FirstPass done"

clean :: FirstPassclean

FirstPassclean :: $(FirstPassclean_dependencies) ##$(cmt_local_FirstPass_makefile)
	$(echo) "(constituents.make) Starting FirstPassclean"
	@-if test -f $(cmt_local_FirstPass_makefile); then \
	  $(MAKE) -f $(cmt_local_FirstPass_makefile) cmt_lock_pid=$${cmt_lock_pid} FirstPassclean; \
	fi

##	  /bin/rm -f $(cmt_local_FirstPass_makefile) $(bin)FirstPass_dependencies.make

install :: FirstPassinstall

FirstPassinstall :: $(FirstPass_dependencies) $(cmt_local_FirstPass_makefile)
	$(echo) "(constituents.make) Starting install FirstPass"
	@-$(MAKE) -f $(cmt_local_FirstPass_makefile) cmt_lock_pid=$${cmt_lock_pid} install
	$(echo) "(constituents.make) install FirstPass done"

uninstall :: FirstPassuninstall

FirstPassuninstall :: $(cmt_local_FirstPass_makefile)
	$(echo) "(constituents.make) Starting uninstall FirstPass"
	@-$(MAKE) -f $(cmt_local_FirstPass_makefile) cmt_lock_pid=$${cmt_lock_pid} uninstall
	$(echo) "(constituents.make) uninstall FirstPass done"

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(constituents.make) Starting $@ FirstPass"
	$(echo) Using default action for $@
	$(echo) "(constituents.make) $@ FirstPass done"
endif


#-- end of constituent ------
#-- start of constituent_lock ------

cmt_make_has_target_tag = 1

#--------------------------------------------------------

ifdef cmt_make_has_target_tag

ifdef READONLY
cmt_local_tagfile_make = /tmp/CMT_$(evestrip_tag)_make.make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_evestrip_makesetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(evestrip_tag)_make.make
cmt_local_tagfile_make = $(bin)$(evestrip_tag)_make.make
cmt_final_setup_make = $(bin)evestrip_makesetup.make
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
cmt_local_tagfile_make = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
cmt_final_setup_make = /tmp/CMT_evestripsetup.make
cmt_local_make_makefile = /tmp/CMT_make$(cmt_lock_pid).make
else
#cmt_local_tagfile_make = $(evestrip_tag).make
cmt_local_tagfile_make = $(bin)$(evestrip_tag).make
cmt_final_setup_make = $(bin)evestripsetup.make
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
cmt_local_tagfile_warnCALIBRECON = /tmp/CMT_$(evestrip_tag)_warnCALIBRECON.make$(cmt_lock_pid)
cmt_final_setup_warnCALIBRECON = /tmp/CMT_evestrip_warnCALIBRECONsetup.make
cmt_local_warnCALIBRECON_makefile = /tmp/CMT_warnCALIBRECON$(cmt_lock_pid).make
else
#cmt_local_tagfile_warnCALIBRECON = $(evestrip_tag)_warnCALIBRECON.make
cmt_local_tagfile_warnCALIBRECON = $(bin)$(evestrip_tag)_warnCALIBRECON.make
cmt_final_setup_warnCALIBRECON = $(bin)evestrip_warnCALIBRECONsetup.make
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
cmt_local_tagfile_warnCALIBRECON = /tmp/CMT_$(evestrip_tag).make$(cmt_lock_pid)
cmt_final_setup_warnCALIBRECON = /tmp/CMT_evestripsetup.make
cmt_local_warnCALIBRECON_makefile = /tmp/CMT_warnCALIBRECON$(cmt_lock_pid).make
else
#cmt_local_tagfile_warnCALIBRECON = $(evestrip_tag).make
cmt_local_tagfile_warnCALIBRECON = $(bin)$(evestrip_tag).make
cmt_final_setup_warnCALIBRECON = $(bin)evestripsetup.make
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
